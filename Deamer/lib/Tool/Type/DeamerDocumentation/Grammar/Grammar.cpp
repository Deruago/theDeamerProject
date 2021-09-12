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

#include "Deamer/Tool/Type/DeamerDocumentation/Grammar/Grammar.h"
#include "Deamer/Language/Reference/ReverseLookup.h"

deamer::tool::type::deamerdocumentation::grammar::Grammar::Grammar(reference reference_)
	: Reference(reference_)
{
}

void deamer::tool::type::deamerdocumentation::grammar::Grammar::Generate(
	::deamer::file::tool::Output& output)
{
	auto grammarDirectory = ::deamer::file::tool::Directory("Grammar");

	auto nonTerminalTemplate =
		templates::deamerdocumentation::grammar::markdown::NonTerminalTemplate();
	const auto nonterminals =
		Reference.GetDefinition<language::type::definition::property::Type::Grammar>().NonTerminals;

	nonTerminalTemplate.production_rule_member_->variable_field_separator_->Set(" ");

	bool startType = true;
	for (language::reference::LDO<language::type::definition::object::main::NonTerminal>
			 nonterminal : nonterminals)
	{
		ImplementNonTerminalInformation(nonTerminalTemplate, nonterminal);

		ImplementNonTerminalReference(nonTerminalTemplate, nonterminal);

		grammarDirectory.AddFile(
			::deamer::file::tool::File(nonterminal->Name, "md", nonTerminalTemplate.GetOutput()));

		startType = false;
	}

	output.AddDirectoryToDocs(grammarDirectory);
}

void deamer::tool::type::deamerdocumentation::grammar::Grammar::ImplementNonTerminalReference(
	templates::deamerdocumentation::grammar::markdown::NonTerminalTemplate& nonTerminalTemplate,
	const language::reference::LDO<language::type::definition::object::main::NonTerminal>
		nonTerminal)
{
	nonTerminalTemplate.nonterminal_reference_->variable_field_->Clear();
	nonTerminalTemplate.production_rule_member_->variable_field_->Clear();
	nonTerminalTemplate.production_rule_->variable_field_->Clear();

	const language::reference::ReverseLookup<
		language::type::definition::object::main::ProductionRule>
		reverseLookupProductionRule(&Reference);

	std::map<language::reference::LDO<language::type::definition::object::main::NonTerminal>,
			 std::vector<language::reference::LDO<
				 language::type::definition::object::main::ProductionRule>>>
		ntToProductionRule;

	const auto result = reverseLookupProductionRule.Get(nonTerminal.Get());
	for (auto productionRule : result.GetObjects())
	{
		language::reference::ReverseLookup<language::type::definition::object::main::NonTerminal>
			reverseLookupNonTerminal(&Reference);
		const auto resultNonTerminals = reverseLookupNonTerminal.Get(productionRule);

		if (resultNonTerminals.IsEmpty())
		{
			continue;
		}

		const auto nonTerminalReference = resultNonTerminals.GetObjects()[0];
		if (ntToProductionRule.find(nonTerminalReference) == ntToProductionRule.end())
		{
			ntToProductionRule[nonTerminalReference] = {};
		}

		ntToProductionRule[nonTerminalReference].push_back(productionRule);
	}

	if (ntToProductionRule.empty())
	{
		nonTerminalTemplate.optional_nonterminal_reference_section_->Set("");
		return;
	}
	else
	{
		nonTerminalTemplate.optional_nonterminal_reference_section_->Set(
			nonTerminalTemplate.nonterminal_reference_section_);
	}

	for (auto [nonTerminal, productionRules] : ntToProductionRule)
	{
		nonTerminalTemplate.referencing_nonterminal_name_->Set(nonTerminal->Name);
		nonTerminalTemplate.production_rule_->variable_field_->Clear();

		for (auto productionRule : productionRules)
		{
			nonTerminalTemplate.production_rule_member_->variable_field_->Clear();
			if (productionRule->Tokens.empty())
			{
				nonTerminalTemplate.production_rule_member_->Set(
					nonTerminalTemplate.production_rule_empty_member_);
				nonTerminalTemplate.production_rule_member_->ExpandVariableField();
			}

			for (language::reference::LDO<::deamer::language::type::definition::object::Base> base :
				 productionRule->Tokens)
			{
				switch (base->Type_)
				{
				case language::type::definition::object::Type::Terminal: {
					nonTerminalTemplate.production_rule_member_name_->Set(
						base.Promote<language::type::definition::object::main::Terminal>()->Name);
					nonTerminalTemplate.production_rule_member_->Set(
						nonTerminalTemplate.production_rule_terminal_member_);
					break;
				}
				case language::type::definition::object::Type::NonTerminal: {
					nonTerminalTemplate.production_rule_member_name_->Set(
						base.Promote<language::type::definition::object::main::NonTerminal>()
							->Name);
					nonTerminalTemplate.production_rule_member_->Set(
						nonTerminalTemplate.production_rule_nonterminal_member_);
					break;
				}
				default:
					break;
				}
				nonTerminalTemplate.production_rule_member_->ExpandVariableField();
			}

			nonTerminalTemplate.production_rule_->ExpandVariableField();
		}

		nonTerminalTemplate.nonterminal_reference_->ExpandVariableField();
	}
}

void deamer::tool::type::deamerdocumentation::grammar::Grammar::ImplementNonTerminalInformation(
	deamer::templates::deamerdocumentation::grammar::markdown::NonTerminalTemplate&
		nonTerminalTemplate,
	deamer::language::reference::LDO<deamer::language::type::definition::object::main::NonTerminal>
		nonterminal)
{
	nonTerminalTemplate.nonterminal_production_rule_->variable_field_->Clear();
	nonTerminalTemplate.nonterminal_reference_->variable_field_->Clear();
	nonTerminalTemplate.production_rule_->variable_field_->Clear();
	nonTerminalTemplate.production_rule_member_->variable_field_->Clear();

	nonTerminalTemplate.nonterminal_name_->Set(nonterminal->Name);
	switch (nonterminal->abstraction)
	{
	case language::type::definition::object::main::NonTerminalAbstraction::Standard:
		nonTerminalTemplate.abstraction_->Set("Standard");
		break;
	case language::type::definition::object::main::NonTerminalAbstraction::Group:
		nonTerminalTemplate.abstraction_->Set("Group");
		break;
	default:
		nonTerminalTemplate.abstraction_->Set("Unknown abstraction");
		break;
	}
	if (nonterminal->IsInlined())
	{
		nonTerminalTemplate.inlined_->Set("Yes");
	}
	else
	{
		nonTerminalTemplate.inlined_->Set("No");
	}

	for (language::reference::LDO<language::type::definition::object::main::ProductionRule>
			 productionRule : nonterminal->ProductionRules)
	{
		nonTerminalTemplate.production_rule_member_->variable_field_->Clear();
		if (productionRule->Tokens.empty())
		{
			nonTerminalTemplate.production_rule_member_->Set(
				nonTerminalTemplate.production_rule_empty_member_);
			nonTerminalTemplate.production_rule_member_->ExpandVariableField();
		}

		for (language::reference::LDO<::deamer::language::type::definition::object::Base> base :
			 productionRule->Tokens)
		{
			switch (base->Type_)
			{
			case language::type::definition::object::Type::Terminal: {
				nonTerminalTemplate.production_rule_member_name_->Set(
					base.Promote<language::type::definition::object::main::Terminal>()->Name);
				nonTerminalTemplate.production_rule_member_->Set(
					nonTerminalTemplate.production_rule_terminal_member_);
				break;
			}
			case language::type::definition::object::Type::NonTerminal: {
				nonTerminalTemplate.production_rule_member_name_->Set(
					base.Promote<language::type::definition::object::main::NonTerminal>()->Name);
				nonTerminalTemplate.production_rule_member_->Set(
					nonTerminalTemplate.production_rule_nonterminal_member_);
				break;
			}
			default:
				break;
			}

			nonTerminalTemplate.production_rule_member_->ExpandVariableField();
		}

		nonTerminalTemplate.nonterminal_production_rule_->ExpandVariableField();
	}
}
