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

#include "Deamer/Lexer/Type/Flex/MainSection.h"

deamer::lexer::type::flex::MainSection::MainSection(const ReferenceType reference_)
	: reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .GetName()
			   ->value)
{
}

std::string deamer::lexer::type::flex::MainSection::Generate() const
{
	return AddStore() + '\n' + AddClear() + '\n' + AddHandleColumn() + '\n' + AddDeamerLexer() +
		   '\n' + CreateMain();
}

std::string deamer::lexer::type::flex::MainSection::AddStore() const
{
	return "static void store(const deamer::external::cpp::lexer::TerminalObject* const "
		   "newObject)\n"
		   "{\n"
		   "\tlocal_objects.push_back(newObject);\n"
		   "}\n";
}

std::string deamer::lexer::type::flex::MainSection::AddClear() const
{
	return "static void clear()\n"
		   "{\n"
		   "\tlocal_objects.clear();\n"
		   "}\n";
}

std::string deamer::lexer::type::flex::MainSection::AddDeamerLexer() const
{
	return "std::vector<const deamer::external::cpp::lexer::TerminalObject*> " + name +
		   "::lexer::Lexer::Tokenize(const std::string& text) const\n"
		   "{\n"
		   "\tlocal_store = true;\n"
		   "\tcolumn = 0;\n"
		   "\n"
		   "\tYY_BUFFER_STATE buf;\n"
		   "\tbuf = yy_scan_string(text.c_str());\n"
		   "\tyylex();\n"
		   "\tyy_delete_buffer(buf);\n"
		   "\tyylex_destroy();\n"
		   "\n"
		   "\tlocal_store = false;\n"
		   "\n"
		   "\tauto local_objects_copy = local_objects;\n"
		   "\tclear();\n"
		   "\n"
		   "\treturn local_objects_copy;\n"
		   "}\n";
}

std::string deamer::lexer::type::flex::MainSection::AddHandleColumn() const
{
	return "static int handleColumn(const std::string& text)\n"
		   "{\n"
		   "\tint currentColumn = column;\n"
		   "\tcurrentColumn += text.size();\n"
		   "\tfor (auto character : text)\n"
		   "\t{\n"
		   "\t\tif (character == '\\n')\n"
		   "\t\t{\n"
		   "\t\t\tcurrentColumn = 0;\n"
		   "\t\t\tbreak;\n"
		   "\t\t}\n"
		   "\t}\n"
		   "\t\n"
		   "\treturn currentColumn;\n"
		   "}\n";
}

std::string deamer::lexer::type::flex::MainSection::CreateMain() const
{
	const auto identity =
		reference.GetDefinition<language::type::definition::property::Type::Identity>();
	const auto generation =
		reference.GetDefinition<language::type::definition::property::Type::Generation>();

	if (generation.IsArgumentSet({tool::type::Tool::Flex, "Debug"}) &&
		!generation.IsIntegrationSet({tool::type::Tool::Flex, tool::type::Tool::Bison}))
	{
		return "int main(int argc,  char** argv)\n"
			   "{\n"
			   "\tstd::string debug_input;\n"
			   "\tfor(auto i = 1; i < argc; i++)\n"
			   "\t{\n"
			   "\t\tdebug_input += argv[i];\n"
			   "\t\tif (i < argc)\n"
			   "\t\t{\n"
			   "\t\t\tdebug_input += ' ';\n"
			   "\t\t}\n"
			   "\t}\n"
			   "\n"
			   "\tauto lexer = " +
			   name +
			   "::lexer::Lexer();\n"
			   "\tauto tokens = lexer.Tokenize(debug_input);\n"
			   "\n"
			   "\treturn 0;\n"
			   "}\n";
	}
	else
	{
		return "";
	}
}
