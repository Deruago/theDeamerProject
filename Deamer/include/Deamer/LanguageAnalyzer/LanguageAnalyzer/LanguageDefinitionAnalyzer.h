/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -July 2020 Thimo B�hmer
 * -August 2020 Thimo B�hmer
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_LANGUAGEDEFINITIONANALYZER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_LANGUAGEDEFINITIONANALYZER_H

#include "Deamer/LanguageGen/LanguageDefinition.h"

namespace deamer
{
	class LanguageDefinitionAnalyzer
	{
	private:
		const LanguageDefinition& languageDefinition;
	public:
		LanguageDefinitionAnalyzer(const LanguageDefinition& languageDefinition_);
		~LanguageDefinitionAnalyzer() = default;

		Token* GetStartToken() const;
		bool DoesTokenHaveEmptyRecursion() const;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_LANGUAGEDEFINITIONANALYZER_H