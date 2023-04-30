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

#include "Deamer/Parser/Type/Dparse/StateEntry.h"
#include "Deamer/Language/Analyzer/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Analyzer/Main/Grammar/ProductionRule.h"
#include "Deamer/Parser/Type/Dparse/StateField.h"

deamer::parser::generator::dparse::StateEntry::StateEntry(
	ReferenceType reference_,
	language::reference::LDO<language::type::definition::object::main::ProductionRule>
		productionRule_,
	std::size_t dotLocation_, const StateField* stateField_, std::shared_ptr<StateEntry> original_)
	: reference(reference_),
	  production(productionRule_),
	  dotLocation(dotLocation_),
	  stateField(stateField_)
{
	if (original_ != nullptr)
	{
		originals.insert(original_);
	}

	nextTokens = NextToken_();
}

deamer::parser::generator::dparse::StateEntry::StateEntry(
	ReferenceType reference_,
	language::reference::LDO<language::type::definition::object::main::ProductionRule>
		productionRule_,
	std::size_t dotLocation_, const StateField* stateField_,
	std::set<std::shared_ptr<StateEntry>> original_)
	: reference(reference_),
	  production(productionRule_),
	  originals(original_),
	  dotLocation(dotLocation_),
	  stateField(stateField_)
{
	nextTokens = NextToken_();
}

deamer::parser::generator::dparse::StateEntry::StateEntry(const StateEntry& rhs)
	: reference(rhs.reference),
	  production(rhs.production),
	  originals(rhs.originals),
	  dotLocation(rhs.dotLocation),
	  nextTokens(rhs.nextTokens),
	  stateField(rhs.stateField)
{
}

std::vector<deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>
deamer::parser::generator::dparse::StateEntry::NextToken_()
{
	if (production == stateField->GetAugmentedPR())
	{
		return {stateField->GetEpsilon()};
	}

	std::set<deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>
		nextTokens_;

	for (auto original : originals)
	{
		auto results = original->GetItemAfterDotItem();
		for (auto result : results)
		{
			if (result->Type_ == language::type::definition::object::Type::Terminal)
			{
				nextTokens_.insert(result);
			}
			else if (result->Type_ == language::type::definition::object::Type::NonTerminal)
			{
				const auto nonTerminalAnalyzer = language::analyzer::main::NonTerminal(
					&reference,
					result.Promote<language::type::definition::object::main::NonTerminal>());
				std::set<
					language::reference::LDO<language::type::definition::object::main::Terminal>>
					ters;
				nonTerminalAnalyzer.GetStartingTerminals(ters);
				if (nonTerminalAnalyzer.CanNonTerminalMatchEmpty())
				{
					nextTokens_.insert(stateField->GetEpsilon());
				}

				for (auto terminal : ters)
				{
					nextTokens_.insert(terminal);
				}
			}
		}
	}

	if (nextTokens_.empty())
	{
		nextTokens_.insert(stateField->GetEpsilon());
	}

	std::vector<deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>
		nextTokens__;
	for (auto element : nextTokens_)
	{
		nextTokens__.push_back(element);
	}

	return nextTokens__;
}

std::vector<deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>
deamer::parser::generator::dparse::StateEntry::NextToken() const
{
	return nextTokens;
}

std::optional<deamer::parser::generator::dparse::StateEntry>
deamer::parser::generator::dparse::StateEntry::CreateNextState() const
{
	// If the dot is at the end, then the next state is undefined
	if (ReachedEnd())
	{
		return std::nullopt;
	}

	// The next state is the pushing the dot
	return StateEntry(reference, production, GetDotLocation() + 1, stateField, originals);
}

bool deamer::parser::generator::dparse::StateEntry::ReachedEnd() const
{
	return GetDotLocation() == production->Tokens.size();
}

bool deamer::parser::generator::dparse::StateEntry::DotPointsToValidElement() const
{
	return GetDotLocation() < production->Tokens.size();
}

std::optional<deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>
deamer::parser::generator::dparse::StateEntry::GetDotNonTerminal() const
{
	if (!DotPointsToValidElement())
	{
		return std::nullopt;
	}

	if (production->Tokens[GetDotLocation()]->Type_ ==
		language::type::definition::object::Type::Terminal)
	{
		return std::nullopt;
	}

	return production->Tokens[GetDotLocation()];
}

std::optional<deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>
deamer::parser::generator::dparse::StateEntry::GetDotItem() const
{
	if (ReachedEnd())
	{
		return std::nullopt;
	}

	return production->Tokens[GetDotLocation()];
}

deamer::language::reference::LDO<deamer::language::type::definition::object::main::ProductionRule>
deamer::parser::generator::dparse::StateEntry::GetProduction() const
{
	return production;
}

std::optional<deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>
deamer::parser::generator::dparse::StateEntry::GetTransitionLdo() const
{
	if (production->Tokens.empty() || GetDotLocation() == 0)
	{
		return std::nullopt;
	}

	return production->Tokens[GetDotLocation() - 1];
}

std::size_t deamer::parser::generator::dparse::StateEntry::GetDotLocation() const
{
	return dotLocation;
}

std::vector<deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>
deamer::parser::generator::dparse::StateEntry::GetItemAfterDotItem()
{
	auto desiredToken = GetDotLocation() + 1;
	if (desiredToken >= production->Tokens.size())
	{
		if (originals.empty())
		{
			return {}; // There is nothing after dot.
		}

		std::vector<
			deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>
			result;
		for (auto i : originals)
		{
			for (auto j : i->GetItemAfterDotItem())
			{
				result.push_back(j);
			}
		}
		return result;
	}

	return {production->Tokens[desiredToken]};
}

bool deamer::parser::generator::dparse::StateEntry::operator>(const StateEntry& rhs) const
{
	if (this == &rhs)
	{
		return false;
	}

	if (GetDotLocation() > rhs.GetDotLocation())
	{
		return true;
	}

	if (production > rhs.production)
	{
		return true;
	}

	return nextTokens > rhs.nextTokens;
}

bool deamer::parser::generator::dparse::StateEntry::operator<(const StateEntry& rhs) const
{
	if (this == &rhs)
	{
		return false;
	}

	if (GetDotLocation() < rhs.GetDotLocation())
	{
		return true;
	}

	if (production < rhs.production)
	{
		return true;
	}

	return nextTokens < rhs.nextTokens;
}

bool deamer::parser::generator::dparse::StateEntry::operator==(const StateEntry& rhs) const
{
	if (this == &rhs)
	{
		return true;
	}

	return CoreEquality(rhs) && LookaheadEquality(rhs);
}

bool deamer::parser::generator::dparse::StateEntry::LookaheadEquality(const StateEntry& rhs) const
{
	return nextTokens == rhs.nextTokens;
}

bool deamer::parser::generator::dparse::StateEntry::CoreEquality(const StateEntry& rhs) const
{
	return GetDotLocation() == rhs.GetDotLocation() && production == rhs.production;
}

void deamer::parser::generator::dparse::StateEntry::Merge(const StateEntry& rhs)
{
	for (auto i : rhs.originals)
	{
		originals.insert(i);
	}

	MergeLookahead(rhs);
}

void deamer::parser::generator::dparse::StateEntry::MergeLookahead(const StateEntry& rhs)
{
	std::set<language::reference::LDO<language::type::definition::object::Base>> newTokens;
	for (auto i : nextTokens)
	{
		newTokens.insert(i);
	}

	for (auto i : rhs.nextTokens)
	{
		newTokens.insert(i);
	}

	nextTokens = std::vector<language::reference::LDO<language::type::definition::object::Base>>(
		newTokens.begin(), newTokens.end());
}

const std::vector<
	deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>&
deamer::parser::generator::dparse::StateEntry::GetLookaheadTokens() const
{
	return nextTokens;
}
