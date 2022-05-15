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

#ifndef DEAMER_PARSER_GENERATOR_DPARSE_STATE_H
#define DEAMER_PARSER_GENERATOR_DPARSE_STATE_H

#include "Deamer/Parser/Type/Dparse/StateEntry.h"
#include <set>

namespace deamer::parser::generator::dparse
{
	class StateField;

	class State
	{
	public:
		using ReferenceType = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar,
			language::type::definition::property::Type::Associativity,
			language::type::definition::property::Type::Precedence>;

	private:
		const ReferenceType reference;

		std::vector<StateEntry> entries;
		StateField* stateField;
		std::map<language::reference::LDO<language::type::definition::object::Base>, State*>
			transitionToState;

	public:
		State(const State& rhs);
		State(ReferenceType reference_,
			  language::reference::LDO<language::type::definition::object::main::NonTerminal>
				  startingNonTerminal,
			  StateField* stateField_);
		State(ReferenceType reference_, StateField* stateField_);

		~State() = default;

	public:
		void Reduce();

		void Next();

	public:
		std::vector<StateEntry> GetEntries() const;
		std::map<language::reference::LDO<language::type::definition::object::Base>, State*>
		GetTransitions() const;

		void AddEntry(const StateEntry& rhs);
		bool DoesEntryExists(const StateEntry& rhs) const;

	public:
		bool operator<(const State& rhs) const;
		bool operator>(const State& rhs) const;
		bool operator==(const State& rhs) const;

	private:
	};
}

#endif // DEAMER_PARSER_GENERATOR_DPARSE_STATE_H
