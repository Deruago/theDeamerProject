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

deamer::ast::type::cpp::Node::Node(const ReferenceType reference_,
								   language::type::definition::object::Base* token_)
	: reference(reference_),
	  token(token_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .name->value)
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
			  languageName + "/Ast/Node/" + languageName +
			  ".h\"\n"
			  "#include <Deamer/External/Cpp/Ast/Node.h>\n"
			  "\n"
			  "namespace " +
			  languageName +
			  " { namespace ast { namespace node {\n"
			  "\n"
			  "\tclass " +
			  tokenName + " : public " + languageName + "<" + tokenName + "> " +
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
			  languageName + "/Ast/Node/" + languageName +
			  ".h\"\n"
			  "#include <Deamer/External/Cpp/Ast/Node.h>\n"
			  "\n"
			  "namespace " +
			  languageName +
			  " { namespace ast { namespace node { \n"
			  "\n"
			  "\tclass " +
			  tokenName + " : public " + languageName + "<" + tokenName + "> " +
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
	return "";
}

std::string deamer::ast::type::cpp::Node::GetBaseNodesToInherit(
	const language::reference::LDO<language::type::definition::object::main::Terminal>& terminal)
	const
{
	return "";
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
