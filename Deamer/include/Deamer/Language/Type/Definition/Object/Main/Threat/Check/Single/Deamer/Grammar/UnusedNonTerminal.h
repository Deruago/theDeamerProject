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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_GRAMMAR_UNUSEDNONTERMINAL_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_GRAMMAR_UNUSEDNONTERMINAL_H

#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Single/Single.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Analyzer/Deamer/Grammar/UnusedNonTerminal.h"

namespace deamer::language::type::definition::property
{
	class Definition;
}

namespace deamer::language::type::definition::object::main::threat::check::deamer::grammar
{
	/*! \class UnusedNonTerminal
	 *
	 *  \brief Checks each terminal on whether they are referenced by the grammar LPD.
	 */
	class UnusedNonTerminal : public Single<property::Type::Grammar>,
							  public CheckOutput<threat::deamer::grammar::UnusedNonTerminal>
	{
	protected:
		/*!	\fn AnalyzeDefinition
		 *
		 *	\brief If the nonterminal is not the start nonterminal, it should be referenced by
		 *	another productionrule not coming from itself. If not it is unused.
		 */
		std::vector<Threat*> AnalyzeDefinition(PropertyReference reference) override
		{
			std::vector<Threat*> threats;

			const auto& grammar = reference.GetDefinition<property::Type::Grammar>();

			for (auto* const nonTerminal : grammar.NonTerminals)
			{
				// The first nonterminal is considered the start nonterminal.
				if (grammar.NonTerminals[0] == nonTerminal)
				{
					continue;
				}

				auto reverseLookup = reference::ReverseLookup<ProductionRule>(&reference);
				const auto& result = reverseLookup.Get(nonTerminal);

				if (result.IsEmpty())
				{
					threats.push_back(new threat::deamer::grammar::UnusedNonTerminal(nonTerminal));
				}

				const auto containsDifferentNonTerminal =
					IsReferencedProductionRuleFromDifferentNonTerminal(reference, nonTerminal,
																	   result);

				if (!containsDifferentNonTerminal)
				{
					threats.push_back(new threat::deamer::grammar::UnusedNonTerminal(nonTerminal));
				}
			}

			return threats;
		}

	private:
		bool IsReferencedProductionRuleFromDifferentNonTerminal(
			PropertyReference reference, NonTerminal* const nonTerminal,
			const reference::ReverseLookupResult<ProductionRule>& result)
		{
			for (const auto& productionrule : result.GetObjects())
			{
				auto reverseLookupNonTerminal = reference::ReverseLookup<NonTerminal>(&reference);
				const auto& resultNonTerminal = reverseLookupNonTerminal.Get(productionrule.Get());

				if (resultNonTerminal.IsEmpty())
				{
					continue;
				}

				for (const auto& productionRuleRootNonterminal : resultNonTerminal.GetObjects())
				{
					if (productionRuleRootNonterminal.Get() != nonTerminal)
					{
						return true;
					}
				}
			}

			return false;
		}
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_GRAMMAR_UNUSEDNONTERMINAL_H
