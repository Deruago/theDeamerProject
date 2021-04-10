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

#include "Deamer/Parser/Type/Bison/IncludeSection.h"

deamer::parser::type::bison::IncludeSection::IncludeSection(
	const generator::bison::Bison::ReferenceType reference_)
	: reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .name->value)
{
}

std::string deamer::parser::type::bison::IncludeSection::Generate() const
{
	return Options() + "%{\n" + Includes() + "\n" + MacroDefine() + "\n" + FunctionPrototypes() +
		   "%}\n";
}

std::string deamer::parser::type::bison::IncludeSection::Includes() const
{
	return AstIncludes() + DefaultIncludes();
}

std::string deamer::parser::type::bison::IncludeSection::DefaultIncludes() const
{
	return "#include <iostream>\n"
		   "#include <vector>\n"
		   "#include <cstring>\n"
		   "#include <stdio.h>\n"
		   "#include <Deamer/External/Cpp/Lexer/TerminalObject.h>\n" +
		   ParserIncludeLocation() + FlexHeaderLocation();
}

std::string deamer::parser::type::bison::IncludeSection::AstIncludes() const
{
	const bool ast =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Bison, tool::type::Tool::DeamerAST});

	if (!ast)
	{
		return "";
	}

	return "";
}

std::string deamer::parser::type::bison::IncludeSection::MacroDefine() const
{
	return "#ifndef YY_parse_NERRS\n"
		   "#define YY_parse_NERRS " +
		   name +
		   "nerrs\n"
		   "#endif //YY_parse_NERRS\n"
		   "#ifndef YY_parse_LLOC\n"
		   "#define YY_parse_LLOC " +
		   name +
		   "lloc\n"
		   "#endif //YY_parse_LLOC\n"
		   "#define YYERROR_VERBOSE\n";
}

std::string deamer::parser::type::bison::IncludeSection::FunctionPrototypes() const
{
	return "void " + name +
		   "error(const char* s);\n"
		   "int " +
		   name + "lex();\n";
}

std::string deamer::parser::type::bison::IncludeSection::ParserIncludeLocation() const
{
	return "#include \"" + name + "/Bison/Parser.h\"\n";
}

std::string deamer::parser::type::bison::IncludeSection::FlexHeaderLocation() const
{
	const bool flex =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Flex, tool::type::Tool::Bison});

	if (!flex)
	{
		return "";
	}

	std::string output;
	if constexpr (file::tool::os_used == file::tool::OSType::os_windows)
	{
		output += "#define YY_NO_UNISTD_H\n";
	}

	output += "#include \"Flex/" + name + "_lexer.h\"\n";

	if constexpr (file::tool::os_used == file::tool::OSType::os_windows)
	{
		output += "#undef YY_NO_UNISTD_H\n";
	}

	return output;
}

std::string deamer::parser::type::bison::IncludeSection::Options() const
{
	if constexpr (deamer::file::tool::os_used == file::tool::OSType::os_windows)
	{
		return "";
	}

	return "";
}
