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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_GRAMMAR_UNUSEDPRODUCTIONRULE_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_GRAMMAR_UNUSEDPRODUCTIONRULE_H

#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Single/Single.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Analyzer/Deamer/Grammar/Type.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Analyzer/Deamer/Grammar/UnusedProductionRule.h"

namespace deamer::language::type::definition::property
{
	class Definition;
}

namespace deamer::language::type::definition::object::main::threat::check::deamer::grammar
{
	/*! \class UnusedProductionRule
	 *
	 *  \brief Each production rule should belong to nonterminal.
	 */
	class UnusedProductionRule : public Single<property::Type::Grammar>,
								 public CheckOutput<threat::deamer::grammar::UnusedProductionRule>
	{
	protected:
		/*!	\fn AnalyzeDefinition
		 *
		 *	\brief If the nonterminal is not the start nonterminal, it should be referenced by
		 *	another nonterminal. If not it is unused.
		 */
		std::vector<Threat*> AnalyzeDefinition(PropertyReference reference) override
		{
			std::vector<Threat*> threats;

			const auto& grammar = reference.GetDefinition<property::Type::Grammar>();

			for (auto* const productionRule : grammar.ProductionRules)
			{
				auto reverseLookup = reference::ReverseLookup<NonTerminal>(&reference);
				const auto& result = reverseLookup.Get(productionRule);

				if (result.IsEmpty())
				{
					threats.push_back(
						new threat::deamer::grammar::UnusedProductionRule(productionRule));
				}
			}

			return threats;
		}
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_GRAMMAR_UNUSEDPRODUCTIONRULE_H
