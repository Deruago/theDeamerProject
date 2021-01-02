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

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEOPTIMISER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEOPTIMISER_H

namespace deamer
{
	class LanguageDefinition;
	class Type;
	class Rule;

	class LanguageOptimiser
	{
	private:
		bool IsTypeUsedByOtherTypes(Type* type) const;
		void RecursivelyRemoveTypeFromLanguageDefinitionIncludingAllRules(Type* type, LanguageDefinition& language_definition) const;

		bool RuleContinuesRecursively(Type* outputTokenOfRule, Rule* rule) const;
		bool IsARuleInTypeAVector(Type* type) const;
		
		bool RuleIsGroupable(Rule* rule) const;
		bool AllRulesOfTypeAreGroupable(Type* type) const;
		void GroupAllRulesOfType(Type* type) const;
	public:
		LanguageOptimiser() = default;
		~LanguageOptimiser() = default;
		void ApplyAllOptimisations(LanguageDefinition& language_definition) const;
		void RemovedUnusedProductionRules(LanguageDefinition& language_definition) const;
		void ApplyEmptyTypeToAllEmptyRules(LanguageDefinition& language_definition) const;
		void ApplyVectorisedTypeToAllRecursiveContinuedRules(LanguageDefinition& language_definition) const;
		void ApplyGroupedTypeToAllGroupableRules(LanguageDefinition& language_definition) const;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEOPTIMISER_H