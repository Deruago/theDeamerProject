/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_TYPEANALYZER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_TYPEANALYZER_H

#include <vector>

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonEmptyRuleFormatter.h"

namespace deamer
{
	class Token;
	
	class TypeAnalyzer
	{
	private:
		void AddTokenToVectorIfNotAlreadyInVector(std::vector<Token*>& tokens, Token* token) const;
	public:
		TypeAnalyzer() = default;
		~TypeAnalyzer() = default;

		std::vector<Token*> GetVectorOfUniqueTokensDefiningThisType(Type& type) const;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_TYPEANALYZER_H