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

#include "Deamer/Parser/Type/Bison/ActionSection.h"

deamer::parser::type::bison::ActionSection::ActionSection(
	const generator::bison::Bison::ReferenceType reference_)
	: reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .name->value)
{
}

std::string deamer::parser::type::bison::ActionSection::Generate() const
{
	return LanguageError() + "\n" + LanguageParser() + "\n" + DebugMain();
}

std::string deamer::parser::type::bison::ActionSection::LanguageError() const
{
	return "void " + name +
		   "error(const char* s)\n"
		   "{\n"
		   "\tstd::cout << \"Syntax error on line: \" << s << '\\n';\n"
		   "}\n";
}

std::string deamer::parser::type::bison::ActionSection::LanguageParser() const
{
	return "deamer::external::cpp::ast::Tree* " + name +
		   "::parser::Parser::Parse(const std::string& text) const\n"
		   "{\n"
		   "\toutputTree = nullptr;\n"
		   "\tYY_BUFFER_STATE buf;\n"
		   "\tbuf = SimpleLang_scan_string(text.c_str());\n"
		   "\tSimpleLangparse();\n"
		   "\tSimpleLang_delete_buffer(buf);\n"
		   "\tSimpleLanglex_destroy();\n"
		   "\n"
		   "\treturn outputTree;\n"
		   "}\n";
}

std::string deamer::parser::type::bison::ActionSection::DebugMain() const
{
	const auto& generation =
		reference.GetDefinition<language::type::definition::property::Type::Generation>();

	if (generation.IsArgumentSet({tool::type::Tool::Flex, "Debug"}) &&
		!generation.IsIntegrationSet({tool::type::Tool::Flex, tool::type::Tool::Bison}))
	{
		return "int main() { return 0; }\n";
	}

	return "";
}
