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

#include "Deamer/Tool/Type/DeamerDocumentation/DeamerDocumentation.h"
#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Template/Tool/Type/DeamerDocumentation/Lexicon/TerminalTemplate.h"

deamer::tool::type::deamerdocumentation::DeamerDocumentation::DeamerDocumentation(
	reference reference_)
	: Base(::deamer::tool::type::Tool::DeamerDocumentation),
	  Reference(reference_)
{
}

deamer::file::tool::Output deamer::tool::type::deamerdocumentation::DeamerDocumentation::Generate()
{
	const auto language_name =
		Reference.GetDefinition<language::type::definition::property::Type::Identity>().name->value;

	file::tool::Output output("DeamerDocumentation");
	auto lexiconDirectory = ::deamer::file::tool::Directory("Lexicon");

	auto terminalTemplate = templates::deamerdocumentation::lexer::markdown::TerminalTemplate();
	const auto& terminals =
		Reference.GetDefinition<language::type::definition::property::Type::Lexicon>().Terminals;
	for (auto i = 0; i < terminals.size(); i++)
	{
		const language::reference::LDO<language::type::definition::object::main::Terminal>
			terminal = terminals[i];

		ImplementTerminalInformation(terminalTemplate, terminals, i, terminal);

		ImplementNonTerminalReferences(terminalTemplate, terminal);

		lexiconDirectory.AddFile(
			::deamer::file::tool::File(terminal->Name, "md", terminalTemplate.GetOutput()));
	}

	output.AddDirectoryToDocs(lexiconDirectory);

	return output;
}

void deamer::tool::type::deamerdocumentation::DeamerDocumentation::ImplementNonTerminalReferences(
	::deamer::templates::deamerdocumentation::lexer::markdown::TerminalTemplate& terminalTemplate,
	const ::deamer::language::reference::LDO<
		deamer::language::type::definition::object::main::Terminal>
		terminal)
{
	terminalTemplate.nonterminal_reference_->variable_field_->Clear();
	terminalTemplate.production_rule_member_->variable_field_->Clear();
	terminalTemplate.production_rule_->variable_field_->Clear();
	terminalTemplate.production_rule_member_->variable_field_separator_->Set(" ");

	const language::reference::ReverseLookup<
		language::type::definition::object::main::ProductionRule>
		reverseLookupProductionRule(&Reference);

	std::map<language::reference::LDO<language::type::definition::object::main::NonTerminal>,
			 std::vector<language::reference::LDO<
				 language::type::definition::object::main::ProductionRule>>>
		ntToProductionRule;

	const auto result = reverseLookupProductionRule.Get(terminal.Get());
	for (auto productionRule : result.GetObjects())
	{
		language::reference::ReverseLookup<language::type::definition::object::main::NonTerminal>
			reverseLookupNonTerminal(&Reference);
		const auto resultNonTerminals = reverseLookupNonTerminal.Get(productionRule);

		if (resultNonTerminals.IsEmpty())
		{
			continue;
		}

		const auto nonTerminal = resultNonTerminals.GetObjects()[0];
		if (ntToProductionRule.find(nonTerminal) == ntToProductionRule.end())
		{
			ntToProductionRule[nonTerminal] = {};
		}

		ntToProductionRule[nonTerminal].push_back(productionRule);
	}

	if (ntToProductionRule.empty())
	{
		terminalTemplate.optional_nonterminal_reference_section_->Set("");
		return;
	}
	else
	{
		terminalTemplate.optional_nonterminal_reference_section_->Set(
			terminalTemplate.nonterminal_reference_section_);
	}

	for (auto [nonTerminal, productionRules] : ntToProductionRule)
	{
		terminalTemplate.nonterminal_name_->Set(nonTerminal->Name);

		for (auto productionRule : productionRules)
		{
			if (productionRule->Tokens.empty())
			{
				terminalTemplate.production_rule_member_->Set(
					terminalTemplate.production_rule_empty_member_);
				terminalTemplate.production_rule_member_->ExpandVariableField();
			}

			for (language::reference::LDO<::deamer::language::type::definition::object::Base> base :
				 productionRule->Tokens)
			{
				switch (base->Type_)
				{
				case language::type::definition::object::Type::Terminal: {
					terminalTemplate.production_rule_member_name_->Set(
						base.Promote<language::type::definition::object::main::Terminal>()->Name);
					terminalTemplate.production_rule_member_->Set(
						terminalTemplate.production_rule_terminal_member_);
					break;
				}
				case language::type::definition::object::Type::NonTerminal: {
					terminalTemplate.production_rule_member_name_->Set(
						base.Promote<language::type::definition::object::main::NonTerminal>()
							->Name);
					terminalTemplate.production_rule_member_->Set(
						terminalTemplate.production_rule_nonterminal_member_);
					break;
				}
				default:
					break;
				}
				terminalTemplate.production_rule_member_->ExpandVariableField();
			}

			terminalTemplate.production_rule_->ExpandVariableField();
		}

		terminalTemplate.nonterminal_reference_->ExpandVariableField();
	}
}

void deamer::tool::type::deamerdocumentation::DeamerDocumentation::ImplementTerminalInformation(
	deamer::templates::deamerdocumentation::lexer::markdown::TerminalTemplate& terminalTemplate,
	const std::vector<deamer::language::type::definition::object::main::Terminal*>& terminals,
	int i,
	const deamer::language::reference::LDO<
		deamer::language::type::definition::object::main::Terminal>
		terminal)
{
	if (i > 0)
	{
		const language::reference::LDO<language::type::definition::object::main::Terminal>
			terminalAbove = terminals[i - 1];
		terminalTemplate.terminal_above_->Set(terminalAbove->Name);
		terminalTemplate.optional_above_neighbour_->Set(terminalTemplate.above_neighbour_);
	}
	else
	{
		terminalTemplate.optional_above_neighbour_->Set("");
	}
	terminalTemplate.terminal_name_->Set(terminal->Name);
	terminalTemplate.regex_value_->Set(terminal->Regex);
	switch (terminal->Special)
	{
	case language::type::definition::object::main::SpecialType::Standard:
		terminalTemplate.abstraction_->Set("Standard");
		break;
	case language::type::definition::object::main::SpecialType::Delete:
		terminalTemplate.abstraction_->Set("Delete");
		break;
	case language::type::definition::object::main::SpecialType::Ignore:
		terminalTemplate.abstraction_->Set("Ignore");
		break;
	case language::type::definition::object::main::SpecialType::NoValue:
		terminalTemplate.abstraction_->Set("NoValue");
		break;
	case language::type::definition::object::main::SpecialType::Crash:
		terminalTemplate.abstraction_->Set("Crash");
		break;
	default:
		terminalTemplate.abstraction_->Set("Unknown abstraction");
		break;
	}
	if ((i + 1) < terminals.size())
	{
		const language::reference::LDO<language::type::definition::object::main::Terminal>
			terminalBelow = terminals[i + 1];
		terminalTemplate.terminal_below_->Set(terminalBelow->Name);
		terminalTemplate.optional_below_neighbour_->Set(terminalTemplate.below_neighbour_);
	}
	else
	{
		terminalTemplate.optional_below_neighbour_->Set("");
	}
}
