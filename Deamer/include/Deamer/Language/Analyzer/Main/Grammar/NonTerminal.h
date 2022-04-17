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

#ifndef DEAMER_LANGUAGE_ANALYZER_MAIN_GRAMMAR_NONTERMINAL_H
#define DEAMER_LANGUAGE_ANALYZER_MAIN_GRAMMAR_NONTERMINAL_H

#include "Deamer/Language/Analyzer/Main/Base.h"
#include "Deamer/Language/Reference/LDO.h"

namespace deamer::language::analyzer::main
{
	/*!	\class NonTerminal
	 *
	 *	\brief Used to analyze NonTerminal LDO's.
	 */
	class NonTerminal : public Base
	{
	private:
		reference::LDO<deamer::language::type::definition::object::main::NonTerminal> nonTerminal;

	public:
		NonTerminal(
			const reference::PropertyDefinitionBase* reference_,
			reference::LDO<deamer::language::type::definition::object::main::NonTerminal, true>
				nonTerminal_);
		~NonTerminal() override = default;

	public:
		/*!	\fn IsRecursive
		 *
		 *	\brief Checks if the nonterminal is recursive till given depth.
		 *
		 *	\details Depth is standard 0, but one may choose to use larger depths.
		 *	The boolean: "infinite" is used to specify it should ignore depth, and continue
		 *endlessly.
		 */
		bool IsRecursive(const size_t depth = 0, const bool infinite = false) const;

		/*!	\fn IsDirectRecursive
		 *
		 *	\brief Checks if the nonterminal is directly recursive.
		 */
		bool IsDirectRecursive() const;

		/*!	\fn IsEventuallyRecursive
		 *
		 *	\brief Checks if the nonterminal is eventually recursive.
		 *
		 *	\details This checks as far as possible.
		 */
		bool IsEventuallyRecursive(const size_t depth) const;

		bool DoesNonTerminalHaveValue() const;

		bool IsStartType() const;

		/*!	\fn GetStartingTerminals
		 *
		 *	\brief This algorithm will found out each possible starting terminal given a
		 *	nonterminal.
		 *
		 *	\see GetEndingTerminals
		 */
		void GetStartingTerminals(
			std::set<reference::LDO<type::definition::object::main::Terminal>>& startingTerminals)
			const;

		/*!	\fn GetEndingTerminals
		 *
		 *	\brief This algorithm will found out each possible ending terminal given a nonterminal.
		 *
		 *	\details This algorithm is O(n^2) (where n is the total tokens in the expanded subtree
		 *	of the nonterminal) for when the grammar underlying the nonterminal is does not end with
		 *	the empty set.
		 *	If it does this introduces multiple branches.
		 *	Increasing the complexity drastically as multiple nonterminals can be reached, possible
		 *	extending to the complete grammar.
		 */
		void GetEndingTerminals(std::set<reference::LDO<type::definition::object::main::Terminal>>&
									endingTerminals) const;

		/*!	\fn DoesNonTerminalHaveEmptyAsItsNode
		 *
		 *	\brief This function checks if a given nonterminal ends or starts with an EMPTY
		 *	(epsilon) terminal.
		 *
		 *	\details This algorithm is O(n) (where n is the total tokens in the expanded subtree
		 *	of the nonterminal).
		 *	If epsilon is found earlier this will be returned earlier.
		 */
		bool DoesNonTerminalHaveEmptyAsItsNode() const;

		bool CanNonTerminalMatchEmpty() const;

		/*!	\fn GetLeftNeighbouringTokens
		 *
		 *	\brief Finds out all subtrees left of this nonterminal.
		 */
		void GetLeftNeighboringTokens(
			std::set<type::definition::object::Base*>& neighboringTokens) const;

		/*!	\fn GetRightNeighboringTokens
		 *
		 *	\brief Finds out all subtrees right of this nonterminal.
		 */
		void GetRightNeighboringTokens(
			std::set<type::definition::object::Base*>& neighboringTokens) const;

		/*!
		 * \fn GetDirectNonTerminalAndTerminals
		 *
		 * \brief Returns all direct accessible (non) terminals.
		 *
		 * \details This function takes in the property of inlined nonterminals.
		 */
		std::set<deamer::language::type::definition::object::Base*>
		GetDirectNonTerminalAndTerminals() const;

	private:
		void GetStartingTerminals(
			std::set<reference::LDO<type::definition::object::main::Terminal>>& startingTerminals,
			std::set<reference::LDO<type::definition::object::main::NonTerminal>>&
				nonTerminalsVisited) const;

		void GetEndingTerminals(
			std::set<reference::LDO<type::definition::object::main::Terminal>>& endingTerminals,
			std::set<reference::LDO<type::definition::object::main::NonTerminal>>&
				nonTerminalsVisited) const;

		void GetLeftNeighboringTokens(
			std::set<type::definition::object::Base*>& neighboringTokens,
			std::set<reference::LDO<type::definition::object::main::NonTerminal>>&
				visitedNonTerminals) const;

		void GetRightNeighboringTokens(
			std::set<type::definition::object::Base*>& set,
			std::set<reference::LDO<type::definition::object::main::NonTerminal>>&
				visitedNonTerminals) const;

		bool DoesNonTerminalHaveEmptyAsItsNode(
			std::set<reference::LDO<type::definition::object::main::NonTerminal>>&
				visitedNonTerminal) const;

		bool CanNonTerminalMatchEmpty(
			std::set<reference::LDO<type::definition::object::main::NonTerminal>>&
				visitedNonTerminal) const;

		bool IsRecursiveImplementation(
			const size_t currentDepth, const size_t maxDepth, const bool infinite,
			reference::LDO<deamer::language::type::definition::object::main::NonTerminal>
				currentNonTerminal,
			std::set<reference::LDO<deamer::language::type::definition::object::main::NonTerminal>>
				currentVisited = {}) const;

		std::set<deamer::language::type::definition::object::Base*>
		GetDirectNonTerminalAndTerminals(
			std::set<deamer::language::type::definition::object::Base*>& symbols,
			std::set<reference::LDO<deamer::language::type::definition::object::main::NonTerminal>>
				visitedNonTerminal = {}) const;
	};
}

#endif // DEAMER_LANGUAGE_ANALYZER_MAIN_GRAMMAR_NONTERMINAL_H
