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

#include "Deamer/Ast/Type/CPP/Visitor.h"

deamer::ast::type::cpp::Visitor::Visitor(ReferenceType reference_)
	: reference(reference_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .GetName()
					   ->value)
{
}

deamer::file::tool::File deamer::ast::type::cpp::Visitor::Generate() const
{
	deamer::file::tool::File baseVisitor("Visitor", "h");

	std::string output;
	output += "#ifndef " + languageName +
			  "_AST_VISITOR_DEAMER_VISITOR_H\n"
			  "#define " +
			  languageName +
			  "_AST_VISITOR_DEAMER_VISITOR_H\n"
			  "\n"
			  "#include <Deamer/External/Cpp/Ast/Visitor.h>\n"
			  "#include \"" +
			  languageName + "/Ast/Node/" + languageName +
			  ".h\"\n"
			  "#include \"" +
			  languageName + "/Ast/Enum/Type.h\"\n" + GenerateTokenIncludes() +
			  "\n"
			  "namespace " +
			  languageName +
			  " { namespace ast { namespace Visitor { \n"
			  "\n"
			  "\tclass Visitor : public ::deamer::external::cpp::ast::Visitor\n"
			  "\t{\n"
			  "\tprivate:\n"
			  "\tpublic:\n"
			  "\t\tVisitor() = default;\n"
			  "\t\t~Visitor() override = default;\n"
			  "\tpublic:\n";

	output += GenerateDispatch();
	output += GenerateVisitorCallbacks();

	output +=
		"\t};\n"
		"\n"
		"}}}\n"
		"\n"
		"#endif // " +
		languageName + "_AST_VISITOR_DEAMER_VISITOR_H\n";

	baseVisitor.SetFileContent(output);

	return baseVisitor;
}

void deamer::ast::type::cpp::Visitor::AddTerminal(
	language::type::definition::object::main::Terminal* terminal)
{
	terminals.emplace_back(terminal);
}

void deamer::ast::type::cpp::Visitor::AddNonTerminal(
	language::type::definition::object::main::NonTerminal* nonTerminal)
{
	nonTerminals.emplace_back(nonTerminal);
}

std::string deamer::ast::type::cpp::Visitor::GenerateTokenIncludes() const
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

std::string deamer::ast::type::cpp::Visitor::GenerateDispatch() const
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
		output += "\t\t\t\tVisit(static_cast<const " + languageName +
				  "::ast::node::" + terminal->Name + "*>(node));\n";
		output += "\t\t\t\tbreak;\n";
		output += "\t\t\t}\n";
	}

	output += "\n";
	for (const auto& nonTerminal : nonTerminals)
	{
		output += "\t\t\tcase " + languageName + "::ast::Type::" + nonTerminal->Name + ":\n";
		output += "\t\t\t{\n";
		output += "\t\t\t\tVisit(static_cast<const " + languageName +
				  "::ast::node::" + nonTerminal->Name + "*>(node));\n";
		output += "\t\t\t\tbreak;\n";
		output += "\t\t\t}\n";
	}

	output +=
		"\t\t\t}\n"
		"\t\t}\n";

	return output;
}

std::string deamer::ast::type::cpp::Visitor::GenerateVisitorCallbacks() const
{
	std::string output;
	for (const auto& terminal : terminals)
	{
		output += "\t\tvirtual void Visit(const " + languageName +
				  "::ast::node::" + terminal->Name + "* node)\n";
		output +=
			"\t\t{\n"
			"\t\t}\n";
	}

	output += "\n";
	for (const auto& nonTerminal : nonTerminals)
	{
		output += "\t\tvirtual void Visit(const " + languageName +
				  "::ast::node::" + nonTerminal->Name + "* node)\n";
		output +=
			"\t\t{\n"
			"\t\t}\n";
	}

	return output;
}
