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

#include "Deamer/Language/Analyzer/Main/Grammar/ProductionRule.h"
#include "Deamer/Language/Analyzer/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include <iostream>

deamer::language::analyzer::main::ProductionRule::ProductionRule(
	const reference::PropertyDefinitionBase* reference_,
	const deamer::language::type::definition::object::main::ProductionRule* productionRule_)
	: Base(reference_),
	  productionRule(productionRule_)
{
	if (productionRule == nullptr)
	{
		throw std::logic_error("productionRule_ was null-pointer");
	}
}

bool deamer::language::analyzer::main::ProductionRule::IsDirectRecursive() const
{
	const reference::ReverseLookup<type::definition::object::main::NonTerminal> reverseLookup(
		language_reference);

	const auto result = reverseLookup.Get(productionRule);

	if (result.Fail() || result.IsEmpty())
	{
		return false;
	}

	return IsDirectRecursive(result.GetObject());
}

bool deamer::language::analyzer::main::ProductionRule::IsDirectRecursive(
	const type::definition::object::main::NonTerminal* nonTerminal) const
{
	for (const auto* const ldo : productionRule->Tokens)
	{
		if (ldo == nonTerminal)
		{
			return true;
		}
	}

	return false;
}

size_t deamer::language::analyzer::main::ProductionRule::GetDirectRecursionPoint() const
{
	const reference::ReverseLookup<type::definition::object::main::NonTerminal> reverseLookup(
		language_reference);
	const auto& result = reverseLookup.Get(productionRule);

	if (!result.Success() || result.IsEmpty())
	{
		throw std::logic_error("Reverse lookup couldn't find the nonterminal this belongs to.");
	}

	return IsDirectRecursive(result.GetObject());
}

size_t deamer::language::analyzer::main::ProductionRule::GetDirectRecursionPoint(
	const type::definition::object::main::NonTerminal* nonTerminal) const
{
	size_t i = 0;

	for (const auto* const ldo : productionRule->Tokens)
	{
		if (ldo == nonTerminal)
		{
			return i;
		}
		i++;
	}

	throw std::logic_error("Production rule is not recursive for given nonterminal.");
}
