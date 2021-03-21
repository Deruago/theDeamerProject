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
	: reference(reference_)
{
}

std::string deamer::lexer::type::flex::MainSection::Generate() const
{
	const auto identity =
		reference.GetDefinition<language::type::definition::property::Type::Identity>();
	const auto generation =
		reference.GetDefinition<language::type::definition::property::Type::Generation>();

	if (generation.IsArgumentSet({tool::type::Tool::Flex, "Debug"}) &&
		!generation.IsIntegrationSet({tool::type::Tool::Flex, tool::type::Tool::Bison}))
	{
		return "int main()\n"
			   "{\n"
			   "\tyylex();\n"
			   "\treturn 0;\n"
			   "}\n";
	}
	else
	{
		return "";
	}
}
