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

#include "Deamer/Ast/Type/CPP/Node.h"
#include "Deamer/Language/Reference/ReverseLookup.h"

deamer::ast::type::cpp::Node::Node(const ReferenceType reference_,
								   language::type::definition::object::Base* token_)
	: reference(reference_),
	  token(token_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .GetName()
					   ->value)
{
}

deamer::file::tool::File deamer::ast::type::cpp::Node::Generate() const
{
	if (token->Type_ == language::type::definition::object::Type::NonTerminal)
	{
		auto nodeFile = GenerateNonTerminal(token);

		return nodeFile;
	}
	if (token->Type_ == language::type::definition::object::Type::Terminal)
	{
		auto nodeFile = GenerateTerminal(token);

		return nodeFile;
	}

	throw std::logic_error("Inputted type, is not terminal or nonterminal");
}

deamer::file::tool::File deamer::ast::type::cpp::Node::GenerateTerminal(
	language::reference::LDO<language::type::definition::object::main::Terminal> terminal) const
{
	const auto& tokenName = terminal->Name;
	deamer::file::tool::File terminalFile(terminal->Name, "h");

	std::string output;
	output += "#ifndef " + languageName + "_AST_NODE_" + tokenName +
			  "_H\n"
			  "#define " +
			  languageName + "_AST_NODE_" + tokenName +
			  "_H\n"
			  "\n"
			  "#include \"" +
			  languageName + "/Ast/Node/" + languageName + ".h\"\n" + GetBaseIncludes(terminal) +
			  "#include <Deamer/External/Cpp/Ast/Node.h>\n"
			  "\n"
			  "namespace " +
			  languageName +
			  " { namespace ast { namespace node {\n"
			  "\n"
			  "\tclass " +
			  tokenName + " : public " + languageName + "<" + tokenName + ">" +
			  GetBaseNodesToInherit(terminal) +
			  "\n"
			  "\t{\n"
			  "\tprivate:\n"
			  "\tpublic:\n"
			  "\t\t" +
			  tokenName +
			  "(deamer::external::cpp::ast::NodeInformation information_)\n"
			  "\t\t: " +
			  languageName + "<" + tokenName + ">(information_, {}, " + GetBaseNodes(terminal) +
			  ")\n"
			  "\t\t{\n"
			  "\t\t}\n"
			  "\t};\n"
			  "\n"
			  "}}}\n"
			  "\n"
			  "#endif // " +
			  languageName + "_AST_NODE_" + terminal->Name + "_H\n";

	terminalFile.SetFileContent(output);

	return terminalFile;
}

deamer::file::tool::File deamer::ast::type::cpp::Node::GenerateNonTerminal(
	language::reference::LDO<language::type::definition::object::main::NonTerminal> nonTerminal)
	const
{
	const auto& tokenName = nonTerminal->Name;
	deamer::file::tool::File nonTerminalFile(nonTerminal->Name, "h");

	std::string output;
	output += "#ifndef " + languageName + "_AST_NODE_" + tokenName +
			  "_H\n"
			  "#define " +
			  languageName + "_AST_NODE_" + tokenName +
			  "_H\n"
			  "\n"
			  "#include \"" +
			  languageName + "/Ast/Node/" + languageName + ".h\"\n" + GetBaseIncludes(nonTerminal) +
			  "#include <Deamer/External/Cpp/Ast/Node.h>\n"
			  "\n"
			  "namespace " +
			  languageName +
			  " { namespace ast { namespace node { \n"
			  "\n"
			  "\tclass " +
			  tokenName + " : public " + languageName + "<" + tokenName + ">" +
			  GetBaseNodesToInherit(nonTerminal) +
			  "\n"
			  "\t{\n"
			  "\tprivate:\n"
			  "\tpublic:\n"
			  "\t\t" +
			  tokenName +
			  "(deamer::external::cpp::ast::NodeInformation information_, "
			  "std::vector<deamer::external::cpp::ast::Node*> nodes_)\n"
			  "\t\t: " +
			  languageName + "<" + tokenName + ">(information_, nodes_, " +
			  GetBaseNodes(nonTerminal) +
			  ")\n"
			  "\t\t{\n"
			  "\t\t}\n"
			  "\t};\n"
			  "\n"
			  "}}}\n"
			  "\n"
			  "#endif // " +
			  languageName + "_AST_NODE_" + nonTerminal->Name + "_H\n";

	nonTerminalFile.SetFileContent(output);

	return nonTerminalFile;
}

std::string deamer::ast::type::cpp::Node::GetBaseNodesToInherit(
	const language::reference::LDO<language::type::definition::object::main::NonTerminal>&
		nonTerminal) const
{
	const auto baseNonTerminals = GetBaseGroupedNodes(nonTerminal);

	std::string output;
	if (nonTerminal->abstraction ==
		language::type::definition::object::main::NonTerminalAbstraction::Group)
	{
		output += ", public ::" + languageName + "::ast::common::node::" + nonTerminal->Name;
	}

	for (language::reference::LDO<language::type::definition::object::main::NonTerminal> baseToken :
		 baseNonTerminals)
	{
		output += ", public ::" + languageName + "::ast::common::node::" + baseToken->Name;
	}

	return output;
}

std::set<const deamer::language::type::definition::object::main::NonTerminal*>
deamer::ast::type::cpp::Node::GetBaseGroupedNodes(
	const deamer::language::reference::LDO<
		deamer::language::type::definition::object::main::Terminal>& terminal) const
{
	language::reference::ReverseLookup<language::type::definition::object::main::ProductionRule>
		lookupRroductionRules(&reference);
	const auto& result = lookupRroductionRules.Get(terminal);

	if (result.Fail() || result.IsEmpty())
	{
		return {};
	}

	const auto& productionRules = result.GetObjects();
	std::set<const deamer::language::type::definition::object::main::NonTerminal*> baseNonTerminals;

	for (const auto& productionRule : productionRules)
	{
		language::reference::ReverseLookup<language::type::definition::object::main::NonTerminal>
			lookupNonTerminal(&reference);
		const auto& resultNonTerminalLookup = lookupNonTerminal.Get(productionRule);

		if (resultNonTerminalLookup.Fail() || resultNonTerminalLookup.IsEmpty())
		{
			continue;
		}

		const auto& resultNonTerminal = resultNonTerminalLookup.GetObject();

		if (resultNonTerminal->abstraction !=
			language::type::definition::object::main::NonTerminalAbstraction::Group)
		{
			continue;
		}

		baseNonTerminals.insert(resultNonTerminal.Get());
	}

	return baseNonTerminals;
}

std::set<const deamer::language::type::definition::object::main::NonTerminal*>
deamer::ast::type::cpp::Node::GetBaseGroupedNodes(
	const deamer::language::reference::LDO<
		deamer::language::type::definition::object::main::NonTerminal>& nonTerminal) const
{
	language::reference::ReverseLookup<language::type::definition::object::main::ProductionRule>
		lookupRroductionRules(&reference);
	const auto& result = lookupRroductionRules.Get(nonTerminal);

	if (result.Fail() || result.IsEmpty())
	{
		return {};
	}

	const auto& productionRules = result.GetObjects();
	std::set<const deamer::language::type::definition::object::main::NonTerminal*> baseNonTerminals;

	for (const auto& productionRule : productionRules)
	{
		language::reference::ReverseLookup<language::type::definition::object::main::NonTerminal>
			lookupNonTerminal(&reference);
		const auto& resultNonTerminalLookup = lookupNonTerminal.Get(productionRule);

		if (resultNonTerminalLookup.Fail() || resultNonTerminalLookup.IsEmpty())
		{
			continue;
		}

		const auto& resultNonTerminal = resultNonTerminalLookup.GetObject();

		if (resultNonTerminal->abstraction !=
			language::type::definition::object::main::NonTerminalAbstraction::Group)
		{
			continue;
		}

		baseNonTerminals.insert(resultNonTerminal.Get());
	}

	return baseNonTerminals;
}

std::string deamer::ast::type::cpp::Node::GetBaseNodesToInherit(
	const language::reference::LDO<language::type::definition::object::main::Terminal>& terminal)
	const
{
	const auto baseNonTerminals = GetBaseGroupedNodes(terminal);

	std::string output;
	for (language::reference::LDO<language::type::definition::object::main::NonTerminal> baseToken :
		 baseNonTerminals)
	{
		output += ", public ::" + languageName + "::ast::common::node::" + baseToken->Name;
	}

	return output;
}

std::string deamer::ast::type::cpp::Node::GetBaseNodes(
	const language::reference::LDO<language::type::definition::object::main::Terminal>& terminal)
	const
{
	return "{}";
}

std::string deamer::ast::type::cpp::Node::GetBaseNodes(
	const language::reference::LDO<language::type::definition::object::main::NonTerminal>&
		nonTerminal) const
{
	return "{}";
}

std::string deamer::ast::type::cpp::Node::GetBaseIncludes(
	const language::reference::LDO<language::type::definition::object::main::Terminal>& terminal)
	const
{
	const auto baseNonTerminals = GetBaseGroupedNodes(terminal);

	std::string output;
	for (language::reference::LDO<language::type::definition::object::main::NonTerminal> baseToken :
		 baseNonTerminals)
	{
		output += "#include \"" + languageName + "/Ast/Node/" + baseToken->Name + ".h\"\n";
	}

	return output;
}

std::string deamer::ast::type::cpp::Node::GetBaseIncludes(
	const language::reference::LDO<language::type::definition::object::main::NonTerminal>&
		nonTerminal) const
{
	const auto baseNonTerminals = GetBaseGroupedNodes(nonTerminal);

	std::string output;

	if (nonTerminal->abstraction ==
		language::type::definition::object::main::NonTerminalAbstraction::Group)
	{
		output += "#include \"" + languageName + "/Ast/Common/Node/" + nonTerminal->Name + ".h\"\n";
	}

	for (language::reference::LDO<language::type::definition::object::main::NonTerminal> baseToken :
		 baseNonTerminals)
	{
		output += "#include \"" + languageName + "/Ast/Node/" + baseToken->Name + ".h\"\n";
	}

	return output;
}
