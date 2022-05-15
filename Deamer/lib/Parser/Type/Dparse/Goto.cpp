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

#include "Deamer/Parser/Type/Dparse/Goto.h"
#include "Deamer/Parser/Type/Dparse/StateField.h"

deamer::parser::type::dparse::Goto::Goto(const generator::dparse::StateField& stateField)
{
	for (auto* state : stateField.GetStates())
	{
		for (auto [transition, outState] : state->GetTransitions())
		{
			if (transition->Type_ != language::type::definition::object::Type::NonTerminal)
			{
				continue;
			}

			mapNonTerminalWithStateTransition[state].insert(
				{transition.Promote<language::type::definition::object::main::NonTerminal>(),
				 stateField.GetIndexOfState(outState)});
		}
	}
}

std::map<::deamer::parser::generator::dparse::State*,
		 std::map<::deamer::language::reference::LDO<
					  ::deamer::language::type::definition::object::main::NonTerminal>,
				  std::size_t>>
deamer::parser::type::dparse::Goto::GetTable() const
{
	return mapNonTerminalWithStateTransition;
}
