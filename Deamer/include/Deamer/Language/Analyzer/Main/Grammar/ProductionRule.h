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

#ifndef DEAMER_LANGUAGE_ANALYZER_MAIN_GRAMMAR_PRODUCTIONRULE_H
#define DEAMER_LANGUAGE_ANALYZER_MAIN_GRAMMAR_PRODUCTIONRULE_H

#include "Deamer/Language/Analyzer/Main/Base.h"
#include "Deamer/Language/Reference/LDO.h"

namespace deamer::language::analyzer::main
{
	class ProductionRule : public Base
	{
	private:
		reference::LDO<deamer::language::type::definition::object::main::ProductionRule>
			productionRule;

	public:
		ProductionRule(
			const reference::PropertyDefinitionBase* reference_,
			reference::LDO<deamer::language::type::definition::object::main::ProductionRule, true>
				productionRule_);
		~ProductionRule() override = default;

	public:
		bool IsDirectRecursive() const;
		bool IsDirectRecursive(
			reference::LDO<type::definition::object::main::NonTerminal> nonTerminal) const;

		/*!	\fn GetDirectRecursionPoint
		 *
		 *	\brief Returns the index it is recursive for the reverse looked up nonterminal.
		 */
		std::size_t GetDirectRecursionPoint() const;

		/*!	\fn GetDirectRecursionPoint
		 *
		 *	\brief Returns the index it is recursive for the given nonterminal.
		 */
		std::size_t GetDirectRecursionPoint(
			reference::LDO<type::definition::object::main::NonTerminal> nonTerminal) const;

		bool IsNonTerminalOwnerOfThisProductionRule(
			reference::LDO<type::definition::object::main::NonTerminal> nonTerminal) const;

		std::size_t GetProductionRuleId() const;
		std::size_t GetProductionRuleId(
			reference::LDO<type::definition::object::main::NonTerminal> nonTerminal) const;

		/*!	\fn GetNonTerminal
		 *
		 *	\brief Returns the nonterminal the production rule belongs to.
		 */
		deamer::language::reference::LDO<
			deamer::language::type::definition::object::main::NonTerminal>
		GetNonTerminal() const;

		bool IsProductionRuleBelongToSomeNonTerminal() const;

	private:
	};
}

#endif // DEAMER_LANGUAGE_ANALYZER_MAIN_GRAMMAR_PRODUCTIONRULE_H
