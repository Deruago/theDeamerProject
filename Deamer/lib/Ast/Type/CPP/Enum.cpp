
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

#include "Deamer/Ast/Type/CPP/Enum.h"

deamer::ast::type::cpp::Enum::Enum(ReferenceType reference_)
	: reference(reference_),
	  languageName(reference_.GetDefinition<language::type::definition::property::Type::Identity>()
					   .name->value)
{
}

deamer::file::tool::File deamer::ast::type::cpp::Enum::Generate() const
{
	deamer::file::tool::File enumFile("Type", "h");

	std::string output;
	output += "#ifndef " + languageName +
			  "_AST_ENUM_TYPE_H\n"
			  "#define " +
			  languageName +
			  "_AST_ENUM_TYPE_H\n"
			  "\n"
			  "namespace " +
			  languageName +
			  " { namespace ast {\n"
			  "\n"
			  "\tenum class Type\n"
			  "\t{\n" +
			  GenerateEnumerations() +
			  "\t};\n"
			  "\n"
			  "}}\n"
			  "\n"
			  "#endif // " +
			  languageName + "_AST_ENUM_TYPE_H\n";

	enumFile.SetFileContent(output);

	return enumFile;
}

void deamer::ast::type::cpp::Enum::AddTerminal(
	language::reference::LDO<language::type::definition::object::main::Terminal> terminal)
{
	terminals.push_back(terminal);
}

void deamer::ast::type::cpp::Enum::AddNonTerminal(
	language::reference::LDO<language::type::definition::object::main::NonTerminal> nonTerminal)

{
	nonTerminals.push_back(nonTerminal);
}

std::string deamer::ast::type::cpp::Enum::GenerateEnumerations() const
{
	std::string output = "\t\t// Reserved\n"
	"\t\tdeamerreserved_unknown,\n"
	"\n";

	output += "\t\t// Terminals\n";
	for (const auto& terminal : terminals)
	{
		output += "\t\t" + terminal->Name + ",\n";
	}

	output += "\n";
	output += "\t\t// Non-Terminals\n";
	for (const auto& nonTerminal : nonTerminals)
	{
		output += "\t\t" + nonTerminal->Name + ",\n";
	}

	return output;
}
