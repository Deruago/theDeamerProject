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

#include "Deamer/Parser/Type/Bison/UnionSection.h"

deamer::parser::type::bison::UnionSection::UnionSection(
	const generator::bison::Bison::ReferenceType reference_)
	: reference(reference_)
{
}

void deamer::parser::type::bison::UnionSection::AddTerminal(
	const language::type::definition::object::main::Terminal& terminal)
{
	terminals.emplace_back(terminal);
}

void deamer::parser::type::bison::UnionSection::AddNonterminal(
	const language::type::definition::object::main::NonTerminal& nonTerminal)
{
	nonTerminals.emplace_back(nonTerminal);
}

void deamer::parser::type::bison::UnionSection::GenerateASTUnionTypes(
	std::string& output, const std::string& languageName) const
{
	const bool ASTintegrate =
		reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Bison, tool::type::Tool::DeamerAST});

	if (!ASTintegrate)
	{
		return;
	}

	for (const auto& terminal : terminals)
	{
		output += "\t" + GetObjectFullType(terminal) + languageName + "_" + terminal.Name + ";\n";
	}

	for (const auto& nonTerminal : nonTerminals)
	{
		output +=
			"\t" + GetObjectFullType(nonTerminal) + languageName + "_" + nonTerminal.Name + ";\n";
	}
}

std::string deamer::parser::type::bison::UnionSection::Generate() const
{
	std::string output;
	const auto& languageName =
		reference.GetDefinition<language::type::definition::property::Type::Identity>().name->value;

	output += "%union{\n";

	GenerateASTUnionTypes(output, languageName);

	output += "}\n";

	return output;
}

std::string deamer::parser::type::bison::UnionSection::GetObjectFullType(
	const language::type::definition::object::main::Terminal& terminal) const
{
	const auto& languageName =
		reference.GetDefinition<language::type::definition::property::Type::Identity>().name->value;

	return languageName + "::ast::" + terminal.Name + "* ";
}
std::string deamer::parser::type::bison::UnionSection::GetObjectFullType(
	const language::type::definition::object::main::NonTerminal& nonTerminal) const
{
	const auto& languageName =
		reference.GetDefinition<language::type::definition::property::Type::Identity>().name->value;

	return languageName + "::ast::" + nonTerminal.Name + "* ";
}
