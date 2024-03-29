/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
/*
 * Part of the DeamerProject.
 * For more information go to: https://github.com/Deruago/theDeamerProject
 */

#include "Deamer/Parser/Type/Dparse/ParserDefinition.h"
#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Template/Parser/Dparse/ParserDefinition/ParserDefinitionTemplate.h"
#include "Deamer/Type/Enum/BitwiseEnum.h"
#include <memory>

deamer::parser::type::dparse::ParserDefinition::ParserDefinition(
	const generator::dparse::Dparse::ReferenceType reference_,
	generator::dparse::StateField& stateField_,
	deamer::type::BitwiseEnum<generator::dparse::Algorithm> algorithm_)
	: reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .GetName()
			   ->value),
	  stateField(stateField_),
	  algorithm(algorithm_)
{
}

std::string deamer::parser::type::dparse::ParserDefinition::Generate() const
{
	if (algorithm.has_flag(generator::dparse::Algorithm::LALR))
	{
		stateField.ApplyLALR(algorithm.has_flag(generator::dparse::Algorithm::Adaptive));
	}
	else if (algorithm.has_flag(generator::dparse::Algorithm::SLR))
	{
		stateField.ApplySLR();
	}

	auto actionTable = stateField.GetActionTable().GetTable();
	auto gotoTable = stateField.GetGotoTable().GetTable();

	auto parserDefinitionTemplate = templates::dparse::parser::ParserDefinitionTemplate();
	parserDefinitionTemplate.goto_table_entry_->Variable_Field_Separator()->Set(" ");
	parserDefinitionTemplate.action_table_entry_->Variable_Field_Separator()->Set(" ");
	parserDefinitionTemplate.language_name_->Set(name);

	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Dleg, tool::type::Tool::Dparse}) ||
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Dparse, tool::type::Tool::Dleg}))
	{
		parserDefinitionTemplate.optional_dleg_include_->Set(
			parserDefinitionTemplate.dleg_include_);
		parserDefinitionTemplate.optional_dleg_usage_->Set(parserDefinitionTemplate.dleg_usage_);
	}

	if (algorithm.has_flag(generator::dparse::Algorithm::General))
	{
		parserDefinitionTemplate.optional_general_option_switch_->Set(
			parserDefinitionTemplate.general_option_switch_);
	}

	auto productionRules =
		reference.GetDefinition<language::type::definition::property::Type::Grammar>()
			.ProductionRules;
	auto terminals =
		reference.GetDefinition<language::type::definition::property::Type::Lexicon>().Terminals;
	auto nonTerminals =
		reference.GetDefinition<language::type::definition::property::Type::Grammar>().NonTerminals;

	parserDefinitionTemplate.state_count_->Set(std::to_string(stateField.GetStates().size()));
	parserDefinitionTemplate.terminal_count_->Set(std::to_string(terminals.size() + 1));
	std::size_t generalOptions = 0;
	for (auto* state : stateField.GetStates())
	{
		parserDefinitionTemplate.action_table_entry_->variable_field_->Clear();
		auto iter = actionTable.find(state);
		if (iter == actionTable.end())
		{
			for (auto i = 0; i < (terminals.size() + 1); i++) // +1 for epsilon at front
			{
				parserDefinitionTemplate.action_table_type_field_->Set("0");
				parserDefinitionTemplate.action_table_specialization_field_->Set(
					std::to_string(stateField.GetStates().size()));

				parserDefinitionTemplate.action_table_entry_->ExpandVariableField();
			}
		}
		else
		{
			auto transitions = iter->second;

			auto iter2 = transitions.find(stateField.GetEpsilon());
			if (iter2 == transitions.end())
			{
				parserDefinitionTemplate.action_table_type_field_->Set("0");
				parserDefinitionTemplate.action_table_specialization_field_->Set(
					std::to_string(stateField.GetStates().size()));

				parserDefinitionTemplate.action_table_entry_->ExpandVariableField();
			}
			else
			{
				auto actionElement = iter2->second;
				if (algorithm.has_flag(generator::dparse::Algorithm::General) &&
					actionElement.size() >
						1) // If it is general parsing and there are multiple items
				{
					// General type, directs parser to use general parsing
					parserDefinitionTemplate.action_table_type_field_->Set("7");
					parserDefinitionTemplate.action_table_specialization_field_->Set(
						std::to_string(generalOptions));
					parserDefinitionTemplate.action_table_entry_->ExpandVariableField();

					parserDefinitionTemplate.general_option_id_->Set(
						std::to_string(generalOptions));

					parserDefinitionTemplate.general_option_shift_reduce_action_->variable_field_
						->Clear();

					for (auto action : actionElement)
					{
						if (action.GetType() == ActionType::Shift)
						{
							if (action.GetTarget() >= stateField.GetStates().size())
							{
								// Invalid
								continue;
							}

							parserDefinitionTemplate.general_option_shift_reduce_action_->Set(
								parserDefinitionTemplate.general_option_shift_impl_);
							parserDefinitionTemplate.general_option_shift_state_->Set(
								std::to_string(action.GetTarget()));
						}
						else if (action.GetType() == ActionType::Accept)
						{
							parserDefinitionTemplate.general_option_shift_reduce_action_->Set(
								parserDefinitionTemplate.general_option_accept_impl_);
						}
						else if (action.GetType() == ActionType::Reduce)
						{
							if (action.GetTarget() >= productionRules.size())
							{
								// Invalid
								continue;
							}

							parserDefinitionTemplate.general_option_shift_reduce_action_->Set(
								parserDefinitionTemplate.general_option_reduce_impl_);
							parserDefinitionTemplate.general_option_reduce_production_rule_->Set(
								std::to_string(action.GetTarget()));
						}
						else
						{
							continue;
						}
						parserDefinitionTemplate.general_option_shift_reduce_action_
							->ExpandVariableField();
					}

					parserDefinitionTemplate.general_option_switch_case_->ExpandVariableField();

					generalOptions++;
				}
				else
				{
					parserDefinitionTemplate.action_table_type_field_->Set(
						std::to_string(static_cast<std::size_t>(actionElement[0].GetType())));
					parserDefinitionTemplate.action_table_specialization_field_->Set(
						std::to_string(actionElement[0].GetTarget()));

					parserDefinitionTemplate.action_table_entry_->ExpandVariableField();
				}
			}

			for (auto* terminal : terminals)
			{
				auto iter3 = transitions.find(terminal);
				if (iter3 == transitions.end())
				{
					parserDefinitionTemplate.action_table_type_field_->Set("0");
					parserDefinitionTemplate.action_table_specialization_field_->Set(
						std::to_string(stateField.GetStates().size()));

					parserDefinitionTemplate.action_table_entry_->ExpandVariableField();
				}
				else
				{
					auto actionElement = iter3->second;
					if (algorithm.has_flag(generator::dparse::Algorithm::General) &&
						actionElement.size() >
							1) // If it is general parsing and there are multiple items
					{
						// General type, directs parser to use general parsing
						parserDefinitionTemplate.action_table_type_field_->Set("7");
						parserDefinitionTemplate.action_table_specialization_field_->Set(
							std::to_string(generalOptions));
						parserDefinitionTemplate.action_table_entry_->ExpandVariableField();

						parserDefinitionTemplate.general_option_id_->Set(
							std::to_string(generalOptions));

						parserDefinitionTemplate.general_option_shift_reduce_action_
							->variable_field_->Clear();

						for (auto action : actionElement)
						{
							if (action.GetType() == ActionType::Shift)
							{
								parserDefinitionTemplate.general_option_shift_reduce_action_->Set(
									parserDefinitionTemplate.general_option_shift_impl_);
								parserDefinitionTemplate.general_option_shift_state_->Set(
									std::to_string(action.GetTarget()));
							}
							else
							{
								parserDefinitionTemplate.general_option_shift_reduce_action_->Set(
									parserDefinitionTemplate.general_option_reduce_impl_);
								parserDefinitionTemplate.general_option_reduce_production_rule_
									->Set(std::to_string(action.GetTarget()));
							}
							parserDefinitionTemplate.general_option_shift_reduce_action_
								->ExpandVariableField();
						}

						parserDefinitionTemplate.general_option_switch_case_->ExpandVariableField();

						generalOptions++;
					}
					else
					{
						parserDefinitionTemplate.action_table_type_field_->Set(
							std::to_string(static_cast<std::size_t>(actionElement[0].GetType())));
						parserDefinitionTemplate.action_table_specialization_field_->Set(
							std::to_string(actionElement[0].GetTarget()));

						parserDefinitionTemplate.action_table_entry_->ExpandVariableField();
					}
				}
			}
		}
		parserDefinitionTemplate.action_table_2d_entry_->ExpandVariableField();
	}

	parserDefinitionTemplate.nonterminal_count_->Set(std::to_string(nonTerminals.size()));
	for (auto* state : stateField.GetStates())
	{
		parserDefinitionTemplate.goto_table_entry_->variable_field_->Clear();
		auto iter = gotoTable.find(state);
		if (iter == gotoTable.end())
		{
			for (auto i = 0; i < nonTerminals.size(); i++)
			{
				parserDefinitionTemplate.goto_table_field_->Set(
					std::to_string(stateField.GetStates().size()));
				parserDefinitionTemplate.goto_table_entry_->ExpandVariableField();
			}
		}
		else
		{
			auto transitions = iter->second;
			for (auto* nonTerminal : nonTerminals)
			{
				auto iter2 = transitions.find(nonTerminal);
				if (iter2 == transitions.end())
				{
					parserDefinitionTemplate.goto_table_field_->Set(
						std::to_string(stateField.GetStates().size()));
					parserDefinitionTemplate.goto_table_entry_->ExpandVariableField();
				}
				else
				{
					parserDefinitionTemplate.goto_table_field_->Set(std::to_string(iter2->second));
					parserDefinitionTemplate.goto_table_entry_->ExpandVariableField();
				}
			}
		}
		parserDefinitionTemplate.goto_table_2d_entry_->ExpandVariableField();
	}

	parserDefinitionTemplate.production_rule_count_->Set(std::to_string(productionRules.size()));
	for (auto* productionRule : productionRules)
	{
		parserDefinitionTemplate.production_rule_size_->Set(
			std::to_string(productionRule->Tokens.size()));

		auto reference = stateField.GetReference();
		auto productionRuleAnalyzer =
			language::analyzer::main::ProductionRule(&reference, productionRule);
		if (productionRuleAnalyzer.GetNonTerminal()->IsReserved())
		{
			parserDefinitionTemplate.production_rule_type_->Set(
				parserDefinitionTemplate.production_rule_type_translation_);
		}
		else
		{
			parserDefinitionTemplate.production_rule_type_->Set(
				parserDefinitionTemplate.production_rule_type_user_);
		}

		parserDefinitionTemplate.production_output_->Set(
			productionRuleAnalyzer.GetNonTerminal()->Name);

		std::size_t productionRuleId = 0;
		for (auto productionRule_ : productionRuleAnalyzer.GetNonTerminal()->ProductionRules)
		{
			if (productionRule == productionRule_)
			{
				break;
			}

			productionRuleId++;
		}
		parserDefinitionTemplate.production_rule_id_->Set(std::to_string(productionRuleId));

		parserDefinitionTemplate.production_id_entry_->ExpandVariableField();
		parserDefinitionTemplate.production_output_entry_->ExpandVariableField();
		parserDefinitionTemplate.production_size_entry_->ExpandVariableField();
		parserDefinitionTemplate.production_type_entry_->ExpandVariableField();
	}

	return parserDefinitionTemplate.GetOutput();
}
