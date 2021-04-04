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

#include "Deamer/Language/Analyzer/Main/Grammar/NonTerminal.h"

deamer::language::analyzer::main::NonTerminal::NonTerminal(
	const reference::PropertyDefinitionBase* reference_,
	const reference::LDO<deamer::language::type::definition::object::main::NonTerminal, true>
		nonTerminal_)
	: Base(reference_),
	  nonTerminal(nonTerminal_)
{
}

bool deamer::language::analyzer::main::NonTerminal::IsRecursive(const size_t depth,
																const bool infinite) const
{
	return IsRecursiveImplementation(0, depth, infinite, nonTerminal);
}

bool deamer::language::analyzer::main::NonTerminal::IsDirectRecursive() const
{
	return IsRecursive(0, false);
}

bool deamer::language::analyzer::main::NonTerminal::IsEventuallyRecursive(const size_t depth) const
{
	return IsRecursive(0, true);
}

bool deamer::language::analyzer::main::NonTerminal::DoesNonTerminalHaveValue() const
{
	return true;
}

bool deamer::language::analyzer::main::NonTerminal::IsRecursiveImplementation(
	const size_t currentDepth, const size_t maxDepth, const bool infinite,
	reference::LDO<deamer::language::type::definition::object::main::NonTerminal>
		currentNonTerminal,
	std::set<reference::LDO<deamer::language::type::definition::object::main::NonTerminal>>
		currentVisited) const
{
	for (const auto* const productionRule : currentNonTerminal->ProductionRules)
	{
		for (const auto* const ldo : productionRule->Tokens)
		{
			if (ldo == nonTerminal)
			{
				return true;
			}
		}
	}

	if (currentDepth >= maxDepth && !infinite)
	{
		return false;
	}

	for (const auto* const productionRule : currentNonTerminal->ProductionRules)
	{
		for (reference::LDO<type::definition::object::main::NonTerminal> ldo :
			 productionRule->Tokens)
		{
			if (ldo == nonTerminal)
			{
				return true;
			}

			if (ldo.IsBaseTypeValid() || currentVisited.count(ldo) > 0)
			{
				continue;
			}

			currentVisited.insert(ldo);

			const bool isRecursive = IsRecursiveImplementation(currentDepth + 1, maxDepth, infinite,
															   ldo, currentVisited);

			if (isRecursive)
			{
				return true;
			}
		}
	}

	return false;
}
