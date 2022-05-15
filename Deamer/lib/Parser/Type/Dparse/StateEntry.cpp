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
	std::size_t dotLocation_, const StateField* stateField_)
	: reference(reference_),
	  production(productionRule_),
	  dotLocation(dotLocation_),
	  stateField(stateField_)
{
	nextTokens = NextToken_();
}

std::vector<deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>
deamer::parser::generator::dparse::StateEntry::NextToken_() const
{
	if (production == stateField->GetAugmentedPR())
	{
		return {stateField->GetEpsilon()};
	}

	const auto productionRuleAnalyzer =
		language::analyzer::main::ProductionRule(&reference, production);
	const auto rootNonTerminal = productionRuleAnalyzer.GetNonTerminal();
	const auto nonTerminalAnalyzer =
		language::analyzer::main::NonTerminal(&reference, rootNonTerminal);

	std::set<::deamer::language::type::definition::object::Base*> neighboringTokens;
	nonTerminalAnalyzer.GetRightNeighboringTokens(neighboringTokens);

	std::set<deamer::language::reference::LDO<deamer::language::type::definition::object::Base>>
		nextTokens_;
	if (neighboringTokens.empty())
	{
		nextTokens_.insert(stateField->GetEpsilon());
	}
	for (auto* neighborToken : neighboringTokens)
	{
		if (neighborToken->Type_ == language::type::definition::object::Type::Terminal)
		{
			nextTokens_.insert(neighborToken);
			continue;
		}

		const auto neighborTokenAnalyzer =
			language::analyzer::main::NonTerminal(&reference, neighborToken);

		if (neighborTokenAnalyzer.CanNonTerminalMatchEmpty())
		{
			nextTokens_.insert(stateField->GetEpsilon());
		}

		std::set<
			language::reference::LDO<::deamer::language::type::definition::object::main::Terminal>>
			startingTerminals;
		neighborTokenAnalyzer.GetStartingTerminals(startingTerminals);
		for (auto startTerminal : startingTerminals)
		{
			nextTokens_.insert(startTerminal);
		}
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
	return StateEntry(reference, production, GetDotLocation() + 1, stateField);
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

	return GetDotLocation() == rhs.GetDotLocation() && production == rhs.production &&
		   nextTokens == rhs.nextTokens;
}
