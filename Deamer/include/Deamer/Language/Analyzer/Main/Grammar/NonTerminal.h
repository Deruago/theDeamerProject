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

namespace deamer::language::analyzer::main
{
	/*!	\class NonTerminal
	 *
	 *	\brief Used to analyze NonTerminal LDO's.
	 */
	class NonTerminal : public Base
	{
	private:
		const deamer::language::type::definition::object::main::NonTerminal* const nonTerminal;

	public:
		NonTerminal(
			const reference::PropertyDefinitionBase* reference_,
			const deamer::language::type::definition::object::main::NonTerminal* nonTerminal_);
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

	private:
		bool IsRecursiveImplementation(
			const size_t currentDepth, const size_t maxDepth, const bool infinite,
			const deamer::language::type::definition::object::main::NonTerminal* const
				currentNonTerminal,
			std::set<const type::definition::object::main::NonTerminal*> currentVisited = {}) const;
	};
}

#endif // DEAMER_LANGUAGE_ANALYZER_MAIN_GRAMMAR_NONTERMINAL_H
