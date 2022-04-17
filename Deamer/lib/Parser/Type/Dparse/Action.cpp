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

#include "Deamer/Parser/Type/Dparse/Action.h"
#include "Deamer/Parser/Type/Dparse/StateField.h"

deamer::parser::type::dparse::ActionElement::ActionElement(ActionType actionType_,
														   std::size_t target_)
	: actionType(actionType_),
	  target(target_)
{
}

deamer::parser::type::dparse::ActionType
deamer::parser::type::dparse::ActionElement::GetType() const
{
	return actionType;
}

std::size_t deamer::parser::type::dparse::ActionElement::GetTarget() const
{
	return target;
}

deamer::parser::type::dparse::Action::Action(const generator::dparse::StateField& stateField)
{
	for (auto* state : stateField.GetStates())
	{
		auto acceptingStateEntry = generator::dparse::StateEntry(
			stateField.GetReference(), stateField.GetAugmentedPR(), 1, &stateField);
		if (state->GetEntries().size() == 1 && state->GetEntries()[0] == acceptingStateEntry)
		{
			AddAction(state, stateField.GetEpsilon(), ActionElement(ActionType::Accept));
			break;
		}
	}

	for (auto* state : stateField.GetStates())
	{
		for (auto [transition, outState] : state->GetTransitions())
		{
			if (transition->Type_ != language::type::definition::object::Type::Terminal)
			{
				continue;
			}

			AddAction(state,
					  transition.Promote<language::type::definition::object::main::Terminal>(),
					  ActionElement(ActionType::Shift, stateField.GetIndexOfState(outState)));
		}
	}

	const auto productionRules =
		stateField.GetReference()
			.GetDefinition<language::type::definition::property::Type::Grammar>()
			.ProductionRules;
	for (auto* state : stateField.GetStates())
	{
		for (auto entry : state->GetEntries())
		{
			if (!entry.ReachedEnd())
			{
				continue;
			}

			std::size_t index = 0;
			for (language::reference::LDO<language::type::definition::object::main::ProductionRule>
					 productionRule : productionRules)
			{
				if (productionRule == entry.GetProduction())
				{
					break;
				}
				index++;
			}

			for (auto lookahead : entry.NextToken())
			{
				AddAction(state, lookahead, ActionElement(ActionType::Reduce, index));
			}
		}
	}
}

std::map<::deamer::parser::generator::dparse::State*,
		 std::map<::deamer::language::reference::LDO<
					  ::deamer::language::type::definition::object::main::Terminal>,
				  std::vector<::deamer::parser::type::dparse::ActionElement>>>
deamer::parser::type::dparse::Action::GetTable() const
{
	return mapLookaheadWithAction;
}

void deamer::parser::type::dparse::Action::AddAction(
	generator::dparse::State* state,
	language::reference::LDO<language::type::definition::object::main::Terminal> ldo,
	const ActionElement& actionElement)
{
	auto iter = mapLookaheadWithAction[state].find(ldo);
	if (iter != mapLookaheadWithAction[state].end())
	{
		iter->second.push_back(actionElement);
	}
	else
	{
		mapLookaheadWithAction[state].insert({ldo, {actionElement}});
	}
}
