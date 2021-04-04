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

#include "Deamer/Parser/Type/Bison/ProductionRuleSection.h"

deamer::parser::type::bison::ProductionRuleSection::ProductionRuleSection(
	const generator::bison::Bison::ReferenceType reference_)
	: reference(reference_)
{
}

std::string deamer::parser::type::bison::ProductionRuleSection::Generate() const
{
	std::string generatedString;

	size_t i = 0;
	for (const auto& nonTerminal : nonTerminalImplementations)
	{
		generatedString += nonTerminal.Generate();

		i++;
		if (i < nonTerminalImplementations.size())
		{
			generatedString += "\n";
		}
	}

	return generatedString;
}

void deamer::parser::type::bison::ProductionRuleSection::AddNonTerminal(
	language::reference::LDO<language::type::definition::object::main::NonTerminal> nonTerminal)
{
	nonTerminalImplementations.emplace_back(reference, nonTerminal);
}
