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

#ifndef DEAMER_PARSER_TYPE_DPARSE_GOTO_H
#define DEAMER_PARSER_TYPE_DPARSE_GOTO_H

#include "Deamer/Parser/Type/Dparse/State.h"
#include <map>

namespace deamer::parser::generator::dparse
{
	class StateField;
}

namespace deamer::parser::type::dparse
{
	/*!	\class Goto
	 *
	 *	\brief Used as Goto table
	 */
	class Goto
	{
	private:
		std::map<generator::dparse::State*,
				 std::map<language::reference::LDO<
							  language::type::definition::object::main::NonTerminal>,
						  std::size_t>>
			mapNonTerminalWithStateTransition;

	public:
		Goto() = default;
		Goto(const generator::dparse::StateField& stateField);
		~Goto() = default;

	public:
		std::map<generator::dparse::State*,
				 std::map<language::reference::LDO<
							  language::type::definition::object::main::NonTerminal>,
						  std::size_t>>
		GetTable() const;

	private:
	};
}

#endif // DEAMER_PARSER_TYPE_DPARSE_GOTO_H
