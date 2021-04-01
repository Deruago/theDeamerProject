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

#include "Deamer/Parser/Type/Bison/Output.h"

deamer::parser::type::bison::Output::Output(const generator::bison::Bison::ReferenceType reference_)
	: reference(reference_),
	  includeSection(reference_),
	  tokenDeclarationSection(reference_),
	  unionSection(reference_),
	  productionRuleSection(reference_),
	  actionSection(reference_)
{
}

void deamer::parser::type::bison::Output::AddTerminal(
	const language::type::definition::object::main::Terminal* terminal)
{
	tokenDeclarationSection.AddTerminal(terminal);
	unionSection.AddTerminal(*terminal);
}

void deamer::parser::type::bison::Output::AddNonTerminal(
	const language::type::definition::object::main::NonTerminal* nonTerminal)
{
	tokenDeclarationSection.AddNonterminal(*nonTerminal);
	unionSection.AddNonterminal(*nonTerminal);
	productionRuleSection.AddNonTerminal(nonTerminal);
}

std::string deamer::parser::type::bison::Output::Generate() const
{
	return includeSection.Generate() + tokenDeclarationSection.Generate() +
		   unionSection.Generate() + "\n%%\n" + productionRuleSection.Generate() + "\n%%\n" +
		   actionSection.Generate();
}
