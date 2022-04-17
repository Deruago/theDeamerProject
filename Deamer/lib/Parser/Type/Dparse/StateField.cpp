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

#include "Deamer/Parser/Type/Dparse/StateField.h"
#include "Deamer/Parser/Type/Dparse/Action.h"
#include "Deamer/Parser/Type/Dparse/Goto.h"

deamer::parser::generator::dparse::StateField::StateField(ReferenceType reference_)
	: reference(reference_),
	  epsilon(new const language::type::definition::object::main::Terminal("$", "[$]")),
	  augmentedStartProductionRule(
		  new const language::type::definition::object::main::ProductionRule(
			  {reference_.GetDefinition<language::type::definition::property::Type::Grammar>()
				   .NonTerminals.at(0)})),
	  augmentedStartNT(new const language::type::definition::object::main::NonTerminal(
		  "reserved_start", {augmentedStartProductionRule.GetRawPointer()}))
{
	const auto& nonTerminals =
		reference.GetDefinition<language::type::definition::property::Type::Grammar>().NonTerminals;
	if (nonTerminals.empty())
	{
		throw std::logic_error("DParse expects an grammar with a NonTerminal");
	}

	states.push_back(new State(reference, augmentedStartNT, this));
}

deamer::parser::generator::dparse::StateField::~StateField()
{
	for (auto* state : states)
	{
		delete state;
	}

	delete epsilon.Get();
	delete augmentedStartProductionRule.Get();
	delete augmentedStartNT.Get();
}

void deamer::parser::generator::dparse::StateField::Compile()
{
	auto unCompiledStates = states;
	while (true)
	{
		std::size_t index = 0;
		for (auto state : unCompiledStates)
		{
			state->Next();
			index++;
		}

		if (states.size() == unCompiledStates.size())
		{
			break;
		}

		// This will recompile earlier states.
		unCompiledStates = states;
	}

	actionTable = type::dparse::Action(*this);
	gotoTable = type::dparse::Goto(*this);
}

deamer::parser::generator::dparse::State*
deamer::parser::generator::dparse::StateField::GetState(State stateRequest)
{
	for (auto* state : states)
	{
		if (*state == stateRequest)
		{
			return state;
		}
	}

	auto* newState = new State(stateRequest);
	states.push_back(newState);
	return newState;
}

std::vector<deamer::parser::generator::dparse::State*>
deamer::parser::generator::dparse::StateField::GetStates() const
{
	return states;
}

deamer::parser::generator::dparse::StateField::ReferenceType
deamer::parser::generator::dparse::StateField::GetReference() const
{
	return reference;
}

std::size_t deamer::parser::generator::dparse::StateField::GetIndexOfState(State* state) const
{
	std::size_t index = 0;
	for (auto ourState : states)
	{
		if (ourState == state)
		{
			return index;
		}

		index++;
	}

	throw std::logic_error("StateField.GetIndexOfState: Given State does not exists.");
}

deamer::parser::type::dparse::Action
deamer::parser::generator::dparse::StateField::GetActionTable() const
{
	return actionTable;
}

deamer::parser::type::dparse::Goto
deamer::parser::generator::dparse::StateField::GetGotoTable() const
{
	return gotoTable;
}

deamer::language::reference::LDO<deamer::language::type::definition::object::main::Terminal>
deamer::parser::generator::dparse::StateField::GetEpsilon() const
{
	return epsilon;
}

deamer::language::reference::LDO<deamer::language::type::definition::object::main::ProductionRule>
deamer::parser::generator::dparse::StateField::GetAugmentedPR() const
{
	return augmentedStartProductionRule;
}

deamer::language::reference::LDO<deamer::language::type::definition::object::main::NonTerminal>
deamer::parser::generator::dparse::StateField::GetAugmentedStart() const
{
	return augmentedStartNT;
}
