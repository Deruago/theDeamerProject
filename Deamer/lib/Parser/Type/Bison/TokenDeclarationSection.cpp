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

#include "Deamer/Parser/Type/Bison/TokenDeclarationSection.h"

deamer::parser::type::bison::TokenDeclarationSection::TokenDeclarationSection(
	const generator::bison::Bison::ReferenceType reference_)
	: reference(reference_),
	  precedenceSection(reference_),
	  associativitySection(reference_)
{
}

void deamer::parser::type::bison::TokenDeclarationSection::AddTerminal(
	const language::type::definition::object::main::Terminal* terminal)
{
	precedenceSection.AddTerminal(*terminal);
	terminalDeclarations.emplace_back(reference, terminal);
}

void deamer::parser::type::bison::TokenDeclarationSection::AddNonterminal(
	const language::type::definition::object::main::NonTerminal& nonTerminal)
{
	nonTerminalDeclarations.emplace_back(reference, nonTerminal);
}

std::string deamer::parser::type::bison::TokenDeclarationSection::Generate() const
{
	std::string output;

	for (const auto& terminalDeclaration : terminalDeclarations)
	{
		output += terminalDeclaration.Generate();
	}

	output += '\n';

	for (const auto& nonTerminalDeclaration : nonTerminalDeclarations)
	{
		output += nonTerminalDeclaration.Generate();
	}

	output += '\n';

	output += precedenceSection.Generate();

	output += '\n';

	output += associativitySection.Generate();

	output += '\n';

	return output;
}
