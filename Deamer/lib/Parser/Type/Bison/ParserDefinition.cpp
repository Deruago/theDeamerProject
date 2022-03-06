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

#include "Deamer/Parser/Type/Bison/ParserDefinition.h"
#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Template/Parser/Bison/ParserDefinition/ParserDefinitionTemplate.h"
#include <memory>

deamer::parser::type::bison::ParserDefinition::ParserDefinition(
	const generator::bison::Bison::ReferenceType reference_)
	: reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .GetName()
			   ->value)
{
}

std::string deamer::parser::type::bison::ParserDefinition::Generate() const
{
	auto parserDefinitionTemplate =
		std::make_unique<templates::bison::parser::ParserDefinitionTemplate>();
	parserDefinitionTemplate->language_name_->Set(name);

	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Bison, "activate-glr"}))
	{
		parserDefinitionTemplate->optional_parse_lac_->Set("");
		parserDefinitionTemplate->optional_glr_setting_->Set(
			parserDefinitionTemplate->glr_setting_);
	}
	
	const auto lexicon =
		reference.GetDefinition<language::type::definition::property::Type::Lexicon>();
	const auto grammar =
		reference.GetDefinition<language::type::definition::property::Type::Grammar>();

	const auto terminals = lexicon.Terminals;
	const auto nonterminals = grammar.NonTerminals;

	for (language::reference::LDO<language::type::definition::object::main::Terminal, false>
			 terminal : terminals)
	{
		parserDefinitionTemplate->token_name_->Set(terminal->Name);
		parserDefinitionTemplate->terminal_declaration_->ExpandVariableField();
		parserDefinitionTemplate->terminal_include_->ExpandVariableField();
		parserDefinitionTemplate->union_declaration_->ExpandVariableField();
	}

	parserDefinitionTemplate->production_rule_->variable_field_separator_->Set("");
	parserDefinitionTemplate->ignore_section_->variable_field_separator_->Set("");

	bool start = true;
	for (language::reference::LDO<language::type::definition::object::main::NonTerminal, false>
			 nonterminal : nonterminals)
	{
		language::analyzer::Analyzer<language::type::definition::object::main::NonTerminal>
			nonterminalAnalyzer(&reference, nonterminal);

		parserDefinitionTemplate->production_rule_->variable_field_->Clear();
		parserDefinitionTemplate->nonterminal_token_name_->Set(nonterminal->Name);
		std::size_t productionRuleIndex = 0;
		for (auto productionRule : nonterminal->ProductionRules)
		{
			parserDefinitionTemplate->production_rule_retrieved_tokens_->variable_field_->Clear();
			parserDefinitionTemplate->production_rule_retrieved_tokens_->variable_field_separator_
				->Set("");
			parserDefinitionTemplate->ignore_section_->variable_field_->Clear();

			if (productionRuleIndex == 0)
			{
				parserDefinitionTemplate->optional_or_->Set("");
			}
			else
			{
				parserDefinitionTemplate->optional_or_->Set(parserDefinitionTemplate->or_);
			}

			parserDefinitionTemplate->production_rule_index_->Set(
				std::to_string(productionRuleIndex));
			productionRuleIndex += 1;

			parserDefinitionTemplate->production_rule_implementation_->Set(
				productionRule->GetText());

			const language::analyzer::Analyzer<
				language::type::definition::object::main::ProductionRule>
				productionRuleAnalyzer(&reference, productionRule);

			if (start && !productionRuleAnalyzer->IsDirectRecursive(nonterminal))
			{
				parserDefinitionTemplate->optional_top_nonterminal_output_->Set(
					parserDefinitionTemplate->top_nonterminal_output_);
			}
			else
			{
				parserDefinitionTemplate->optional_top_nonterminal_output_->Set("");
			}

			if (nonterminal->IsReserved())
			{
				parserDefinitionTemplate->production_rule_type_->Set("translation");
			}
			else
			{
				parserDefinitionTemplate->production_rule_type_->Set("user");
			}

			std::size_t index = 1;
			bool addObject = false;
			for (auto object : productionRule->Tokens)
			{
				if (index != 1 && addObject)
				{
					parserDefinitionTemplate->optional_comma_->Set(", ");
				}
				else
				{
					parserDefinitionTemplate->optional_comma_->Set("");
				}
				parserDefinitionTemplate->token_index_->Set(std::to_string(index));

				if (object->Type_ == language::type::definition::object::Type::Terminal)
				{
					const language::reference::LDO<
						language::type::definition::object::main::Terminal, false>
						terminal(object);
					parserDefinitionTemplate->token_name_->Set(terminal->Name);
					switch (terminal->Special)
					{
					case language::type::definition::object::main::SpecialType::NoValue:
					case language::type::definition::object::main::SpecialType::Standard: {
						parserDefinitionTemplate->production_rule_retrieved_tokens_impl_->Set(
							parserDefinitionTemplate->transfer_terminal_);
						parserDefinitionTemplate->production_rule_retrieved_tokens_
							->ExpandVariableField();
						addObject = true;
						break;
					}
					case language::type::definition::object::main::SpecialType::Crash:
					case language::type::definition::object::main::SpecialType::Delete:
					case language::type::definition::object::main::SpecialType::Ignore:
					default: {
						parserDefinitionTemplate->ignore_section_->ExpandVariableField();
						break;
					}
					}
				}
				else if (object->Type_ == language::type::definition::object::Type::NonTerminal)
				{
					const language::reference::LDO<
						language::type::definition::object::main::NonTerminal, false>
						objectNonTerminal(object);
					parserDefinitionTemplate->token_name_->Set(objectNonTerminal->Name);
					parserDefinitionTemplate->production_rule_retrieved_tokens_impl_->Set(
						parserDefinitionTemplate->transfer_nonterminal_);
					parserDefinitionTemplate->production_rule_retrieved_tokens_
						->ExpandVariableField();
					addObject = true;
				}
				else
				{
					// Invalid LDO
				}

				index += 1;
			}

			parserDefinitionTemplate->production_rule_->ExpandVariableField();
		}

		parserDefinitionTemplate->token_name_->Set(nonterminal->Name);
		parserDefinitionTemplate->nonterminal_declaration_->ExpandVariableField();
		parserDefinitionTemplate->nonterminal_include_->ExpandVariableField();
		parserDefinitionTemplate->union_declaration_->ExpandVariableField();
		start = false;
		parserDefinitionTemplate->nonterminal_implementation_->ExpandVariableField();
	}

	return parserDefinitionTemplate->GetOutput();
}
