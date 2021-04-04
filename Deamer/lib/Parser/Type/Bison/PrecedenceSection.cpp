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

#include "Deamer/Parser/Type/Bison/PrecedenceSection.h"
#include "Deamer/Language/Reference/ReverseLookup.h"

deamer::parser::type::bison::PrecedenceSection::PrecedenceSection(
	const generator::bison::Bison::ReferenceType reference_)
	: reference(reference_)
{
}

void deamer::parser::type::bison::PrecedenceSection::AddTerminal(
	language::reference::LDO<language::type::definition::object::main::Terminal> terminal)
{
	const auto precedence =
		language::reference::ReverseLookup<
			language::type::definition::object::main::ObjectPrecedence>(&reference)
			.Get(terminal);

	if (precedence.IsEmpty())
	{
		return;
	}

	const auto terminalPrecedence = precedence.GetObject()->Precedence;

	for (size_t i = 0; i < terminals.size(); i++)
	{
		const auto& currentTerminal = terminals[i];
		if (currentTerminal.first <= terminalPrecedence)
		{
			terminals.insert(terminals.begin() + i, {terminalPrecedence, terminal});
			return;
		}
	}
	terminals.insert(terminals.end(), {terminalPrecedence, terminal});
}

std::string deamer::parser::type::bison::PrecedenceSection::Generate() const
{
	return "";
	if (terminals.empty())
	{
		return "";
	}

	std::vector<std::string> generatedStrings;
	int currentPrecedence = terminals[0].first;
	for (const auto& [precedence, terminal] : terminals)
	{
		const std::string currentString = "%precedence " + terminal->Name + "\n";
		generatedStrings.push_back(currentString);
	}

	std::string output;
	for (const auto& generatedString : generatedStrings)
	{
		output += generatedString;
	}

	return output;
}
