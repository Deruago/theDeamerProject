/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_H
#include <vector>

#include "Deamer/ParserGen/BisonBuilder/BisonRuleSectionFormatter.h"

namespace deamer
{
	class LanguageDefinition;

	class LanguageAnalyzer
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
		LanguageAnalyzer() = default;
		~LanguageAnalyzer() = default;
		void ApplyAllOptimisations(LanguageDefinition& language_definition) const;
		void RemovedUnusedProductionRules(LanguageDefinition& language_definition) const;
		void ApplyEmptyTypeToAllEmptyRules(LanguageDefinition& language_definition) const;
		void ApplyVectorisedTypeToAllRecursiveContinuedRules(LanguageDefinition& language_definition) const;
		void ApplyGroupedTypeToAllGroupableRules(LanguageDefinition& language_definition) const;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_H