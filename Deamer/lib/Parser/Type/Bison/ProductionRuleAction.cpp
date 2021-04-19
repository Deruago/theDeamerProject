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
	  productionRuleAnalyzer(&reference, productionRule),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .name->value)
{
}

std::string deamer::parser::type::bison::ProductionRuleAction::Generate() const
{
	return GenerateDebug() + ConstructObject() + AssignObject() + ExportObject();
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
	return languageName + "::ast::node::" + nonTerminal->Name;
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

	return LanguageName + "::ast::node::" + terminal.Name;
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
				const language::reference::LDO<language::type::definition::object::main::Terminal>
					terminal(ldo);

				// language::ast::terminal($index)
				arguments.push_back("new " + ObjectFullName(*terminal.Get()) + "(" +
									GenerateNodeinformation(terminal, i) + ")");
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

	return arguments;
}

std::string deamer::parser::type::bison::ProductionRuleAction::ConstructObject() const
{
	const bool integrateAST =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Bison, tool::type::Tool::DeamerAST});

	if (!integrateAST)
	{
		return "";
	}
	std::string output;
	output +=
		"\t\t"
		"auto* const newNode = "
		"new " +
		ObjectFullName() + "(" + GenerateNodeinformation(nonTerminal) + ", { " +
		ObjectArgumentList() + " }" + ")" + ";\n";

	return output;
}

std::string deamer::parser::type::bison::ProductionRuleAction::GenerateNodeinformation(
	language::reference::LDO<language::type::definition::object::main::Terminal> terminal,
	size_t currentIndex) const
{
	const std::string nodeValue = "::deamer::external::cpp::ast::NodeValue::terminal";

	std::string output;
	output += "{::" + languageName + "::ast::Type::" + terminal->Name + ", " + nodeValue + ", $" +
			  std::to_string(currentIndex) + "}";

	return output;
}

std::string deamer::parser::type::bison::ProductionRuleAction::GenerateNodeinformation(
	language::reference::LDO<language::type::definition::object::main::NonTerminal> nonTerminal)
	const
{
	std::string nodeValue;

	const auto vector =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsArgumentSet({tool::type::Tool::Bison, "Vector"});

	if (vector)
	{
		nodeValue = "::deamer::external::cpp::ast::NodeValue::vector";
	}
	else
	{
		nodeValue = "::deamer::external::cpp::ast::NodeValue::nonterminal";
	}

	std::string output;
	output += "{::" + languageName + "::ast::Type::" + nonTerminal->Name + ", " + nodeValue +
			  ", {" + std::to_string(productionRuleAnalyzer->GetProductionRuleId(nonTerminal)) +
			  ", ::deamer::external::cpp::ast::ProductionRuleType::user}}";

	return output;
}

std::string deamer::parser::type::bison::ProductionRuleAction::ExportObject() const
{
	const auto ast =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Bison, tool::type::Tool::DeamerAST});

	if (!ast)
	{
		return "";
	}

	bool startType = false;
	const auto& nonTerminals =
		reference.GetDefinition<language::type::definition::property::Type::Grammar>().NonTerminals;
	if (nonTerminals.empty())
	{
		startType = false;
	}
	else
	{
		startType = nonTerminals[0] == nonTerminal;
	}

	if (!startType)
	{
		return "";
	}

	if (productionRuleAnalyzer->IsDirectRecursive(nonTerminal))
	{
		return "";
	}

	return "\t\toutputTree = new ::deamer::external::cpp::ast::Tree(newNode);\n";
}
