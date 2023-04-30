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

#ifndef DEAMER_PARSER_GENERATOR_DPARSE_STATEFIELD_H
#define DEAMER_PARSER_GENERATOR_DPARSE_STATEFIELD_H

#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/ProductionRule.h"
#include "Deamer/Parser/Type/Dparse/Action.h"
#include "Deamer/Parser/Type/Dparse/Goto.h"
#include "Deamer/Parser/Type/Dparse/State.h"

namespace deamer::parser::generator::dparse
{
	class StateField
	{
	public:
		using ReferenceType = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar,
			language::type::definition::property::Type::Associativity,
			language::type::definition::property::Type::Precedence>;

	private:
		const ReferenceType reference;
		std::vector<State*> states;
		type::dparse::Action actionTable;
		type::dparse::Goto gotoTable;
		language::reference::LDO<language::type::definition::object::main::Terminal> epsilon;
		language::reference::LDO<language::type::definition::object::main::ProductionRule>
			augmentedStartProductionRule;
		language::reference::LDO<language::type::definition::object::main::NonTerminal>
			augmentedStartNT;
		std::vector<State*> oldStates;
		State* startState;

	public:
		StateField(ReferenceType reference_);
		~StateField();
		void ReloadAction();
		void ReloadGoto();

	public:
		void Compile();

		State* GetState(State stateRequest);

		std::vector<State*> GetStates() const;
		ReferenceType GetReference() const;
		std::size_t GetIndexOfState(State* state) const;

		type::dparse::Action GetActionTable() const;
		type::dparse::Goto GetGotoTable() const;

		language::reference::LDO<language::type::definition::object::main::Terminal>
		GetEpsilon() const;
		language::reference::LDO<language::type::definition::object::main::ProductionRule>
		GetAugmentedPR() const;
		language::reference::LDO<language::type::definition::object::main::NonTerminal>
		GetAugmentedStart() const;

	public:
		void ApplyLALR(bool adaptive = true);

		void ApplySLR();

	private:
	};
}

#endif // DEAMER_PARSER_GENERATOR_DPARSE_STATEFIELD_H
