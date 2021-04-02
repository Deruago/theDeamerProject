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

#include "Deamer/Language/Type/Definition/Property/Main/Lexicon.h"

deamer::language::type::definition::property::main::Lexicon::Lexicon(
	std::vector<object::main::Terminal*> terminals_)
	: Definition(Type::Lexicon),
	  Terminals(std::move(terminals_))
{
	references.Add(Terminals);
}

const deamer::language::type::definition::object::main::Terminal* deamer::language::type::definition::property::main::
Lexicon::GetTerminal(const std::string& terminalName) const
{
	for (const auto* const terminal : Terminals)
	{
		if (terminal->Name == terminalName)
		{
			return terminal;
		}
	}

	return nullptr;
}
