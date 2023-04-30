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

#include "Deamer/Parser/Type/Dparse/State.h"
#include "Deamer/Parser/Type/Dparse/StateField.h"

deamer::parser::generator::dparse::State::State(const State& rhs)
	: reference(rhs.reference),
	  entries(rhs.entries),
	  stateField(rhs.stateField),
	  transitionToState(rhs.transitionToState)
{
	for (auto [_, outState] : transitionToState)
	{
		outState->statesReferencingThisState.insert(this);
	}
}

deamer::parser::generator::dparse::State::State(
	ReferenceType reference_,
	language::reference::LDO<language::type::definition::object::main::NonTerminal>
		startingNonTerminal,
	StateField* stateField_)
	: reference(reference_),
	  stateField(stateField_)
{
	for (auto* production : startingNonTerminal->ProductionRules)
	{
		AddEntry(StateEntry(reference, production, 0, stateField));
	}

	Reduce();
}

deamer::parser::generator::dparse::State::State(ReferenceType reference_, StateField* stateField_)
	: reference(reference_),
	  stateField(stateField_)
{
}

void deamer::parser::generator::dparse::State::Reduce()
{
	std::vector<StateEntry> evaluateEntries = entries;
	while (!evaluateEntries.empty())
	{
		std::vector<StateEntry> newStateEntries;

		for (auto& entry : evaluateEntries)
		{
			auto nonTerminal = entry.GetDotNonTerminal();

			if (!nonTerminal.has_value())
			{
				// It is a terminal, thus skipping it
				continue;
			}

			for (auto* productionRule :
				 nonTerminal.value()
					 .Promote<language::type::definition::object::main::NonTerminal>()
					 ->ProductionRules)
			{
				// If the production rule is empty, the state is reducable.
				newStateEntries.emplace_back(reference, productionRule, 0, stateField,
											 std::make_shared<StateEntry>(entry));
			}
		}

		evaluateEntries.clear();
		for (const auto& newStateEntry : newStateEntries)
		{
			if (DoesEntryExists(newStateEntry))
			{
				continue;
			}

			AddEntry(newStateEntry);
			evaluateEntries.push_back(newStateEntry);
		}
	}
}

void deamer::parser::generator::dparse::State::Next()
{
	std::map<language::reference::LDO<language::type::definition::object::Base>, State> newStates;
	for (auto entry : entries)
	{
		auto item = entry.GetDotItem();
		if (!item.has_value())
		{
			// Entry is already finished
			continue;
		}

		auto nextEntry = entry.CreateNextState();
		if (!nextEntry.has_value())
		{
			// Entry is already finished
			continue;
		}

		auto iter = transitionToState.find(item.value());
		if (iter != transitionToState.end())
		{
			// The state can only exists if it is finalized.
			// Thus skip it
			continue;
		}

		auto iter2 = newStates.find(item.value());
		if (iter2 == newStates.end())
		{
			newStates.insert({{item.value()}, {State(reference, stateField)}});
		}
		newStates.find(item.value())->second.AddEntry(nextEntry.value());
	}

	for (auto& [transition, state] : newStates)
	{
		state.Reduce(); // The state must be fully reduced. This way we guarantee uniqueness
		auto nextState = stateField->GetState(state);
		nextState->statesReferencingThisState.insert(this);
		transitionToState.insert({transition, nextState});
	}
}

std::vector<deamer::parser::generator::dparse::StateEntry>
deamer::parser::generator::dparse::State::GetEntries() const
{
	return entries;
}

std::map<deamer::language::reference::LDO<deamer::language::type::definition::object::Base>,
		 deamer::parser::generator::dparse::State*>
deamer::parser::generator::dparse::State::GetTransitions() const
{
	return transitionToState;
}

void deamer::parser::generator::dparse::State::AddEntry(const StateEntry& rhs)
{
	if (DoesEntryExists(rhs))
	{
		return;
	}

	entries.push_back(rhs);
}

bool deamer::parser::generator::dparse::State::DoesEntryExists(const StateEntry& rhs)
{
	for (auto& entry : entries)
	{
		if (!entry.LookaheadEquality(rhs))
		{
			if (entry.CoreEquality(rhs))
			{
				entry.Merge(rhs);
				return true;
			}
		}

		if (entry.CoreEquality(rhs))
		{
			return true;
		}
	}

	return false;
}

bool deamer::parser::generator::dparse::State::operator<(const State& rhs) const
{
	if (this == &rhs)
	{
		return false;
	}

	return this->entries < rhs.entries;
}

bool deamer::parser::generator::dparse::State::operator>(const State& rhs) const
{
	if (this == &rhs)
	{
		return false;
	}

	return this->entries > rhs.entries;
}

bool deamer::parser::generator::dparse::State::operator==(const State& rhs) const
{
	if (this == &rhs)
	{
		return true;
	}

	return this->entries == rhs.entries;
}

bool deamer::parser::generator::dparse::State::CoreEquivalent(State* value)
{
	if (entries.size() != value->entries.size())
	{
		return false;
	}

	for (auto entry : entries)
	{
		bool coreEquivalent = false;
		for (auto targetEntry : value->entries)
		{
			if (targetEntry.CoreEquality(entry))
			{
				coreEquivalent = true;
				break;
			}
		}

		if (!coreEquivalent)
		{
			return false;
		}
	}

	return true;
}

bool deamer::parser::generator::dparse::State::LookaheadEquivalent(State* value)
{
	if (entries.size() != value->entries.size())
	{
		return false;
	}

	for (auto entry : entries)
	{
		bool coreEquivalent = false;
		for (auto targetEntry : value->entries)
		{
			if (targetEntry.LookaheadEquality(entry))
			{
				coreEquivalent = true;
				break;
			}
		}

		if (!coreEquivalent)
		{
			return false;
		}
	}

	return true;
}

bool deamer::parser::generator::dparse::State::FullyEquivalent(State* value)
{
	return CoreEquivalent(value) && LookaheadEquivalent(value);
}

bool deamer::parser::generator::dparse::State::TryMerge(State* state)
{
	const auto currentTotalRrIssues = GetReduceReduceConflicts(entries);

	auto copyEntries = entries;
	for (auto& entry : copyEntries)
	{
		for (auto& targetEntry : state->entries)
		{
			if (!entry.CoreEquality(targetEntry))
			{
				continue;
			}

			entry.Merge(targetEntry);
		}
	}

	const auto newTotalRrIssues = GetReduceReduceConflicts(copyEntries);

	// LALR Merging can only introduce Reduce/Reduce conflicts.
	// Thus Shift/Reduce conflicts are irrelevant.
	if (newTotalRrIssues <= currentTotalRrIssues)
	{
		entries = std::move(copyEntries);

		for (auto* _ : state->statesReferencingThisState)
		{
			_->Update(state, this);
		}
		return true;
	}

	return false;
}

void deamer::parser::generator::dparse::State::Merge(State* state)
{
	for (auto& entry : entries)
	{
		for (auto& targetEntry : state->entries)
		{
			if (!entry.CoreEquality(targetEntry))
			{
				continue;
			}

			entry.Merge(targetEntry);
		}
	}

	for (auto* _ : state->statesReferencingThisState)
	{
		_->Update(state, this);
	}
}

void deamer::parser::generator::dparse::State::Update(State* oldState, State* newState)
{
	for (auto& _ : transitionToState)
	{
		if (_.second != oldState)
		{
			continue;
		}

		_.second = newState;
	}
}

std::size_t deamer::parser::generator::dparse::State::GetShiftReduceConflicts(
	const std::vector<StateEntry>& vector)
{
	throw std::logic_error("Unimplemented");
}

std::size_t deamer::parser::generator::dparse::State::GetReduceReduceConflicts(
	const std::vector<StateEntry>& vector)
{
	std::size_t conflicts = 0;
	for (const auto& entry : vector)
	{
		for (const auto& targetEntry : vector)
		{
			if (&targetEntry == &entry)
			{
				continue;
			}

			if (ReduceConflictBetween(entry, targetEntry))
			{
				conflicts++;
			}
		}
	}

	return conflicts;
}

bool deamer::parser::generator::dparse::State::ReduceConflictBetween(const StateEntry& lhs,
																	 const StateEntry& rhs)
{
	if (&lhs == &rhs)
	{
		// Entry cannot conflict with itself
		return false;
	}

	if (!(lhs.ReachedEnd() && rhs.ReachedEnd()))
	{
		return false;
	}

	if (lhs.GetProduction() == rhs.GetProduction())
	{
		// If they have the same productions, the lookahead must be merged. (No reduce conflict)
		return false;
	}

	std::set<language::reference::LDO<language::type::definition::object::Base>> lhsTokens = {
		lhs.GetLookaheadTokens().begin(), lhs.GetLookaheadTokens().end()};

	std::set<language::reference::LDO<language::type::definition::object::Base>> rhsTokens = {
		rhs.GetLookaheadTokens().begin(), rhs.GetLookaheadTokens().end()};

	auto check = [&](std::set<language::reference::LDO<language::type::definition::object::Base>>&
						 largeTokens,
					 std::set<language::reference::LDO<language::type::definition::object::Base>>&
						 smallTokens) {
		for (auto& i : largeTokens)
		{
			if (smallTokens.find(i) == smallTokens.end())
			{
				continue;
			}

			// The same lookahead can reduce two different productions.
			return true;
		}

		return false;
	};

	if (lhsTokens.size() >= rhsTokens.size())
	{
		return check(lhsTokens, rhsTokens);
	}

	return check(rhsTokens, lhsTokens);
}
