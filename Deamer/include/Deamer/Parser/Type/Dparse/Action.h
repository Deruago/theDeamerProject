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

#ifndef DEAMER_PARSER_TYPE_DPARSE_ACTION_H
#define DEAMER_PARSER_TYPE_DPARSE_ACTION_H

#include "Deamer/Parser/Type/Dparse/State.h"

namespace deamer::parser::generator::dparse
{
	class StateField;
}

namespace deamer::parser::type::dparse
{
	enum class ActionType
	{
		unknown,

		Shift,
		Reduce,
		Accept,
		Reject, // Reserved
	};

	struct ActionElement
	{
	private:
		ActionType actionType;

		// Reduce utilizes this as ProductionRule index
		// Shift utilizes this as state transition index
		std::size_t target;

	public:
		ActionElement(ActionType actionType_, std::size_t target_ = 0);
		~ActionElement() = default;

	public:
		ActionType GetType() const;
		std::size_t GetTarget() const;
	};

	/*!	\class Action
	 *
	 *	\brief Used as Action table
	 */
	class Action
	{
	private:
		std::map<
			generator::dparse::State*,
			std::map<language::reference::LDO<language::type::definition::object::main::Terminal>,
					 std::vector<ActionElement>>>
			mapLookaheadWithAction;

	public:
		Action() = default;
		Action(const generator::dparse::StateField& stateField);
		~Action() = default;

	public:
		std::map<
			generator::dparse::State*,
			std::map<language::reference::LDO<language::type::definition::object::main::Terminal>,
					 std::vector<ActionElement>>>
		GetTable() const;

	private:
		void
		AddAction(generator::dparse::State* state,
				  language::reference::LDO<language::type::definition::object::main::Terminal> ldo,
				  const ActionElement& actionElement);
	};
}

#endif // DEAMER_PARSER_TYPE_DPARSE_ACTION_H
