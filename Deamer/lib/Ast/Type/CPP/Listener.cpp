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

#include "Deamer/Ast/Type/CPP/Listener.h"

deamer::ast::type::cpp::Listener::Listener(ReferenceType reference_)
	: reference(reference_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .GetName()
					   ->value)
{
}

deamer::file::tool::File deamer::ast::type::cpp::Listener::Generate() const
{
	deamer::file::tool::File baseListener("Listener", "h");

	std::string output;
	output += "#ifndef " + languageName +
			  "_AST_LISTENER_DEAMER_LISTENER_H\n"
			  "#define " +
			  languageName +
			  "_AST_LISTENER_DEAMER_LISTENER_H\n"
			  "\n"
			  "#include <Deamer/External/Cpp/Ast/Listener.h>\n"
			  "#include \"" +
			  languageName + "/Ast/Node/" + languageName +
			  ".h\"\n"
			  "#include \"" +
			  languageName + "/Ast/Enum/Type.h\"\n" + GenerateTokenIncludes() +
			  "\n"
			  "namespace " +
			  languageName +
			  " { namespace ast { namespace listener { \n"
			  "\n"
			  "\tclass Listener : public ::deamer::external::cpp::ast::Listener\n"
			  "\t{\n"
			  "\tprivate:\n"
			  "\tpublic:\n"
			  "\t\tListener() = default;\n"
			  "\t\t~Listener() override = default;\n"
			  "\tpublic:\n";

	output += GenerateDispatch();
	output += GenerateListenerCallbacks();

	output +=
		"\t};\n"
		"\n"
		"}}}\n"
		"\n"
		"#endif // " +
		languageName + "_AST_LISTENER_DEAMER_LISTENER_H\n";

	baseListener.SetFileContent(output);

	return baseListener;
}

void deamer::ast::type::cpp::Listener::AddTerminal(
	language::type::definition::object::main::Terminal* terminal)
{
	terminals.emplace_back(terminal);
}

void deamer::ast::type::cpp::Listener::AddNonTerminal(
	language::type::definition::object::main::NonTerminal* nonTerminal)
{
	nonTerminals.emplace_back(nonTerminal);
}

std::string deamer::ast::type::cpp::Listener::GenerateTokenIncludes() const
{
	std::string output;
	for (const auto& terminal : terminals)
	{
		output += "#include \"" + languageName + "/Ast/Node/" + terminal->Name + ".h\"\n";
	}

	output += "\n";
	for (const auto& nonTerminal : nonTerminals)
	{
		output += "#include \"" + languageName + "/Ast/Node/" + nonTerminal->Name + ".h\"\n";
	}
	return output;
}

std::string deamer::ast::type::cpp::Listener::GenerateDispatch() const
{
	std::string output;
	output +=
		"\t\tvoid Dispatch(const ::deamer::external::cpp::ast::Node* node) override\n"
		"\t\t{\n"
		"\t\t\tconst auto enumeratedValue = static_cast<" +
		languageName +
		"::ast::Type>(node->GetType());\n"
		"\t\t\tswitch(enumeratedValue)\n"
		"\t\t\t{\n";
	for (const auto& terminal : terminals)
	{
		output += "\t\t\tcase " + languageName + "::ast::Type::" + terminal->Name + ":\n";
		output += "\t\t\t{\n";
		output += "\t\t\t\tListen(static_cast<const " + languageName +
				  "::ast::node::" + terminal->Name + "*>(node));\n";
		output += "\t\t\t\tbreak;\n";
		output += "\t\t\t}\n";
	}

	output += "\n";
	for (const auto& nonTerminal : nonTerminals)
	{
		output += "\t\t\tcase " + languageName + "::ast::Type::" + nonTerminal->Name + ":\n";
		output += "\t\t\t{\n";
		output += "\t\t\t\tListen(static_cast<const " + languageName +
				  "::ast::node::" + nonTerminal->Name + "*>(node));\n";
		output += "\t\t\t\tDefaultAction(node);\n";
		output += "\t\t\t\tbreak;\n";
		output += "\t\t\t}\n";
	}

	output +=
		"\t\t\t}\n"
		"\t\t}\n";

	return output;
}

std::string deamer::ast::type::cpp::Listener::GenerateListenerCallbacks() const
{
	std::string output;
	for (const auto& terminal : terminals)
	{
		output += "\t\tvirtual void Listen(const " + languageName +
				  "::ast::node::" + terminal->Name + "* node)\n";
		output +=
			"\t\t{\n"
			"\t\t}\n";
	}

	output += "\n";
	for (const auto& nonTerminal : nonTerminals)
	{
		output += "\t\tvirtual void Listen(const " + languageName +
				  "::ast::node::" + nonTerminal->Name + "* node)\n";
		output +=
			"\t\t{\n"
			"\t\t}\n";
	}

	output +=
		"\tprivate:\n"
		"\t\tvoid DefaultAction(const ::deamer::external::cpp::ast::Node* node)\n"
		"\t\t{\n"
		"\t\t\tfor(const auto* child : node->GetNodes())\n"
		"\t\t\t{\n"
		"\t\t\t\tDispatch(child);\n"
		"\t\t\t}\n"
		"\t\t}\n";
	return output;
}
