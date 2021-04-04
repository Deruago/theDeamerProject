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

#include "Deamer/Lexer/Type/Flex/IncludeSection.h"

deamer::lexer::type::flex::IncludeSection::IncludeSection(ReferenceType reference_)
	: reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .name->value)
{
}

std::string deamer::lexer::type::flex::IncludeSection::Generate() const
{
	return "%option yylineno\n"
		   "%option noyywrap\n"
		   "\n"
		   "%{\n"
		   "#include <iostream>\n"
		   "#include <string>\n"
		   "#include <stdio.h>\n"
		   "#include <string.h>\n"
		   "#include <Deamer/External/Cpp/Lexer/TerminalObject.h>\n"
		   //		   "#include <"+ name + "/Flex/Extern/Lexer.h>\n" +
		   "#include \"./Lexer.h\"\n" +
		   ParserInclude() +
		   "void showError();\n"
		   "extern int " +
		   name +
		   "lex();\n"
		   "\n"
		   "static bool local_store = false;\n"
		   "static void store(const deamer::external::cpp::lexer::TerminalObject* const "
		   "newObject);\n"
		   "static std::vector<const deamer::external::cpp::lexer::TerminalObject*> "
		   "local_objects;\n" +
		   RedefineMacros() + "%}\n";
}

std::string deamer::lexer::type::flex::IncludeSection::ParserInclude() const
{
	const bool bison =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Flex, tool::type::Tool::Bison});

	if (!bison)
	{
		return "";
	}

	return "#include \"./" + name + "_parser.tab.h\"\n";
}

std::string deamer::lexer::type::flex::IncludeSection::ParserMacroRedefine() const
{
	const bool bison =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Flex, tool::type::Tool::Bison});

	if (bison)
	{
		return "";
	}

	return "#ifndef " + name + "lval\n" + "struct " + name +
		   "lval_t {\n"
		   "deamer::external::lexer::TerminalObject* Terminal = nullptr;\n"
		   "};\n"
		   "auto " +
		   name + "lval = " + name +
		   "lval_t();\n"
		   "#endif // " +
		   name + "lval\n";
}

std::string deamer::lexer::type::flex::IncludeSection::RedefineMacros() const
{
	return ParserMacroRedefine() +
		   "#ifndef yyval\n"
		   "#define yyval yytext\n"
		   "#endif //yyval\n";
}
