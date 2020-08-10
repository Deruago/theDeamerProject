/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -July 2020 Thimo B�hmer
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