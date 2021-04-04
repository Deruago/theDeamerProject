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

#include "Deamer/Parser/Type/Bison/ProductionRuleAction.h"
#include "Deamer/Language/Analyzer/Analyzer.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include <type_traits>

deamer::parser::type::bison::ProductionRuleAction::ProductionRuleAction(
	const generator::bison::Bison::ReferenceType reference_,
	language::reference::LDO<language::type::definition::object::main::NonTerminal> nonTerminal_,
	language::reference::LDO<language::type::definition::object::main::ProductionRule>
		productionRule_)
	: reference(reference_),
	  nonTerminal(nonTerminal_),
	  productionRule(productionRule_),
	  nonterminalAnalyzer(&reference, nonTerminal),
	  productionRuleAnalyzer(&reference, productionRule)
{
}

std::string deamer::parser::type::bison::ProductionRuleAction::Generate() const
{
	return GenerateDebug() + ConstructObject() + AssignObject();
}

std::string deamer::parser::type::bison::ProductionRuleAction::GenerateDebug() const
{
	const bool debug =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Bison, "Debug"});
	if (debug)
	{
		return "\t\t"
			   "std::cout << \"Found an NonTerminal: " +
			   nonTerminal->Name + "\" << \"\\n\";\n";
	}

	return "";
}

std::string deamer::parser::type::bison::ProductionRuleAction::ObjectFullName() const
{
	const std::string LanguageName =
		reference.GetDefinition<language::type::definition::property::Type::Identity>().name->value;

	return LanguageName + "::ast::" + nonTerminal->Name;
}

std::string deamer::parser::type::bison::ProductionRuleAction::AssignObject() const
{
	const bool ast =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Bison, tool::type::Tool::DeamerAST});

	const bool vector =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Bison, "Vector"});

	const language::reference::ReverseLookup<
		deamer::language::type::definition::object::main::NonTerminal>
		reverseLookup(&reference);

	const auto result = reverseLookup.Get(productionRule);

	if (!ast)
	{
		return "";
	}

	if (vector)
	{
		if (nonterminalAnalyzer->IsDirectRecursive())
		{
			if (productionRuleAnalyzer->IsDirectRecursive(nonTerminal))
			{
				return "\t\t"
					   "$$ = $" +
					   std::to_string(productionRuleAnalyzer->GetDirectRecursionPoint(nonTerminal) +
									  1) +
					   "\n" + "\t\t" + "$$->push_back(newNode);\n";
			}
			else
			{
				return "\t\t"
					   "$$ = new std::vector<" +
					   ObjectFullName() + ">();\n";
			}
		}
	}

	return "\t\t"
		   "$$ = newNode;\n";
}

std::string deamer::parser::type::bison::ProductionRuleAction::ObjectFullName(
	const language::type::definition::object::main::Terminal& terminal) const
{
	const std::string LanguageName =
		reference.GetDefinition<language::type::definition::property::Type::Identity>().name->value;

	return LanguageName + "::ast::" + terminal.Name;
}

std::vector<std::string>
deamer::parser::type::bison::ProductionRuleAction::GetSequenceOfValidArguments() const
{
	const bool vector =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Bison, "Vector"});

	std::vector<std::string> arguments;
	size_t i = 1;
	for (auto* ldo : productionRule->Tokens)
	{
		const std::string currentArgumentIndex = "$" + std::to_string(i);
		switch (ldo->Type_)
		{
		case language::type::definition::object::Type::NonTerminal: {
			if (nonterminalAnalyzer->DoesNonTerminalHaveValue())
			{
				if (vector && productionRuleAnalyzer->IsNonTerminalOwnerOfThisProductionRule(ldo))
				{
					break;
				}

				arguments.push_back(currentArgumentIndex);
			}
			break;
		}
		case language::type::definition::object::Type::Terminal: {
			const auto terminalAnalyzer =
				language::analyzer::Analyzer<language::type::definition::object::main::Terminal>(
					&reference, ldo);

			if (terminalAnalyzer->DoesTerminalHaveValue())
			{
				// language::ast::terminal($index)
				arguments.push_back(
					"new " +
					ObjectFullName(
						*static_cast<language::type::definition::object::main::Terminal*>(ldo)) +
					"(" + currentArgumentIndex + ")");
			}
			break;
		}
		default:
			break;
		}

		i++;
	}

	return arguments;
}

std::string deamer::parser::type::bison::ProductionRuleAction::ObjectArgumentList() const
{
	const auto validArguments = GetSequenceOfValidArguments();
	std::string arguments;
	size_t i = 0;
	for (const auto& argument : validArguments)
	{
		arguments += argument;
		i++;
		if (i < validArguments.size())
		{
			arguments += ", ";
		}
	}

	return "(" + arguments + ")";
}

std::string deamer::parser::type::bison::ProductionRuleAction::ConstructObject() const
{
	const bool integrateAST =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Bison, tool::type::Tool::DeamerAST});

	if (productionRule->IsEmpty())
	{
		return "";
	}

	if (!integrateAST)
	{
		return "";
	}

	return "\t\t"
		   "auto* const newNode = "
		   "new " +
		   ObjectFullName() + ObjectArgumentList() + ";\n";
}
