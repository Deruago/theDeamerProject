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

#include "Deamer/Parser/Type/Bison/AssociativitySection.h"
#include "Deamer/Language/Reference/ReverseLookup.h"

deamer::parser::type::bison::AssociativitySection::AssociativitySection(
	const generator::bison::Bison::ReferenceType reference_)
	: reference(reference_)
{
}

void deamer::parser::type::bison::AssociativitySection::AddTerminal(
	language::reference::LDO<language::type::definition::object::main::Terminal> terminal)
{
	const auto& associativity =
		language::reference::ReverseLookup<
			language::type::definition::object::main::ObjectAssociativity>(&reference)
			.Get(terminal);
	if (associativity.IsEmpty())
	{
		return;
	}
	const auto& terminalAssociativity = associativity.GetObject()->Associativity;

	terminals.emplace_back(terminalAssociativity, terminal);
}

std::string deamer::parser::type::bison::AssociativitySection::Generate() const
{
	std::string output;

	for (const auto& [associativity, terminal] : terminals)
	{
		switch (associativity)
		{
		case language::type::definition::object::main::AssociativityType::left: {
			output += "%left " + terminal->Name + '\n';
			break;
		}
		case language::type::definition::object::main::AssociativityType::right: {
			output += "%right " + terminal->Name + '\n';
			break;
		}
		case language::type::definition::object::main::AssociativityType::any: {
			break;
		}
		}
	}

	return output;
}
