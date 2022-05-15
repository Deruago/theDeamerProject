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

#ifndef DEAMER_PARSER_GENERATOR_DPARSE_STATEENTRY_H
#define DEAMER_PARSER_GENERATOR_DPARSE_STATEENTRY_H

#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/ProductionRule.h"

namespace deamer::parser::generator::dparse
{
	class StateField;

	class StateEntry
	{
	public:
		using ReferenceType = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar,
			language::type::definition::property::Type::Associativity,
			language::type::definition::property::Type::Precedence>;

	private:
		const ReferenceType reference;

		language::reference::LDO<language::type::definition::object::main::ProductionRule>
			production;
		std::size_t dotLocation;
		std::vector<language::reference::LDO<language::type::definition::object::Base>> nextTokens;
		const StateField* stateField;

	public:
		StateEntry(
			ReferenceType reference_,
			language::reference::LDO<language::type::definition::object::main::ProductionRule>
				productionRule_,
			std::size_t dotLocation_, const StateField* stateField_);
		~StateEntry() = default;

	public:
		/*!	\fn NextToken
		 *
		 *	\brief Returns the lookahead tokens. This can include epsilon
		 *
		 *	\note The Epsilon token is recognized by checking the LDO address with nullptr.
		 *	The Epsilon token is a nullptr.
		 */
		std::vector<language::reference::LDO<language::type::definition::object::Base>>
		NextToken() const;

		/*!	\fn CreateNextState
		 *
		 *	\brief Creates the next state if there is such state
		 *
		 *	\details
		 *	Given the state entry:
		 *	`S -> .BC , $
		 *
		 *	This function outputs:
		 *	`S -> B.C , $
		 *
		 *	If there is no next state, this function returns nothing.
		 */
		std::optional<StateEntry> CreateNextState() const;

		/*!	\fn ReachedEnd
		 *
		 *	\brief Checks if the Dot location is at the end
		 */
		bool ReachedEnd() const;

		bool DotPointsToValidElement() const;
		/*!	\fn GetDotNonTerminal
		 *
		 *	\brief Returns the NT at the dot location. If it is a terminal, nothing is returned.
		 */
		std::optional<language::reference::LDO<language::type::definition::object::Base>>
		GetDotNonTerminal() const;

		/*!	\fn GetDotItem
		 *
		 *	\brief Returns the item the dot is at. If there is no item (i.e. finished) nothing is
		 *returned.
		 */
		std::optional<language::reference::LDO<language::type::definition::object::Base>>
		GetDotItem() const;

		language::reference::LDO<language::type::definition::object::main::ProductionRule>
		GetProduction() const;

		std::optional<language::reference::LDO<language::type::definition::object::Base>>
		GetTransitionLdo() const;

		std::size_t GetDotLocation() const;

	public:
		bool operator>(const StateEntry& rhs) const;
		bool operator<(const StateEntry& rhs) const;
		bool operator==(const StateEntry& rhs) const;

	private:
		std::vector<language::reference::LDO<language::type::definition::object::Base>>
		NextToken_() const;
	};
}

#endif // DEAMER_PARSER_GENERATOR_DPARSE_STATEENTRY_H
