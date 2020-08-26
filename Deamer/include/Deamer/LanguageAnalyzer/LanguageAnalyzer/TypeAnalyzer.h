/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_TYPEANALYZER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_TYPEANALYZER_H

#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include <vector>

namespace deamer
{
	class Token;
	struct TokenAppearance;
	
	class TypeAnalyzer
	{
	private:
		Type* type_;
		void AddTokenToVectorIfNotAlreadyInVector(std::vector<Token*>& tokens, Token* token) const;

		Rule* CreateRule_Without_Ignored_Tokens(Rule* rule) const;
		bool IsThisRuleUniqueInVector(const std::vector<Rule*>& rules, const Rule& rule) const;
		bool AreRulesEqual(const Rule& rule1, const Rule& rule2) const;
	public:
		TypeAnalyzer(Type& type);
		~TypeAnalyzer() = default;

		std::vector<Token*> GetVectorOfUniqueTokensDefiningThisType() const;
		// i.e: t: a a, a a a returns vector with a a a. as a a a is minimal amount of tokens that are needed to cover all rules.
		std::vector<deamer::TokenAppearance> GetVectorOfMinimalAmountOfTokensUsedDefiningThisType() const;
		std::vector<Rule*> GetVectorOfUniqueRulesApplyingIgnoredTokens() const;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_TYPEANALYZER_H