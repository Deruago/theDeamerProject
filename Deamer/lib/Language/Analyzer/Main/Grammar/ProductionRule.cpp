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
	reference::LDO<deamer::language::type::definition::object::main::ProductionRule, true>
		productionRule_)
	: Base(reference_),
	  productionRule(productionRule_)
{
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
	reference::LDO<type::definition::object::main::NonTerminal> nonTerminal) const
{
	for (reference::LDO<type::definition::object::main::NonTerminal> ldo : productionRule->Tokens)
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

	const auto result = reverseLookup.Get(productionRule);

	if (!result.Success() || result.IsEmpty())
	{
		throw std::logic_error("Reverse lookup couldn't find the nonterminal this belongs to.");
	}

	return IsDirectRecursive(result.GetObject());
}

size_t deamer::language::analyzer::main::ProductionRule::GetDirectRecursionPoint(
	reference::LDO<type::definition::object::main::NonTerminal> nonTerminal) const
{
	size_t i = 0;

	for (reference::LDO<type::definition::object::main::NonTerminal> ldo : productionRule->Tokens)
	{
		if (ldo == nonTerminal)
		{
			return i;
		}
		i++;
	}

	throw std::logic_error("Production rule is not recursive for given nonterminal.");
}

bool deamer::language::analyzer::main::ProductionRule::IsNonTerminalOwnerOfThisProductionRule(
	reference::LDO<type::definition::object::main::NonTerminal> nonTerminal) const
{
	for (reference::LDO<::deamer::language::type::definition::object::main::ProductionRule>
			 productionRule_ : nonTerminal->ProductionRules)
	{
		if (productionRule_ == productionRule)
		{
			return true;
		}
	}

	return false;
}

size_t deamer::language::analyzer::main::ProductionRule::GetProductionRuleId() const
{
	const reference::ReverseLookup<type::definition::object::main::NonTerminal> reverseLookup(
		language_reference);

	const auto result = reverseLookup.Get(productionRule);

	if (result.Fail() || result.IsEmpty())
	{
		throw std::runtime_error("Couldn't find non terminal, this productionrule belongs to!");
	}

	return GetProductionRuleId(result.GetObject());
}

size_t deamer::language::analyzer::main::ProductionRule::GetProductionRuleId(
	reference::LDO<type::definition::object::main::NonTerminal> nonTerminal) const
{
	size_t count = 0;

	for (auto* productionRule_ : nonTerminal->ProductionRules)
	{
		if (productionRule_ == productionRule)
		{
			return count;
		}

		count++;
	}

	throw std::runtime_error("Production rule is not in nonterminal!");
}
