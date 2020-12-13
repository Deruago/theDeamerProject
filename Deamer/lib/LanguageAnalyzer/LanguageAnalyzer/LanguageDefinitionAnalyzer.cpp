/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"

deamer::LanguageDefinitionAnalyzer::LanguageDefinitionAnalyzer(const LanguageDefinition& languageDefinition_)
{
	languageDefinition = languageDefinition_;
}

deamer::Token* deamer::LanguageDefinitionAnalyzer::GetStartToken() const
{
	if (languageDefinition.StartType != nullptr)
		return languageDefinition.StartType;
	else
		if (languageDefinition.Types.empty())
			return nullptr;
		else
			return languageDefinition.Types[0];
}

// This is done by finding a cycle from NT a to NT a, via NT's.
// The analysis is extremely complex as a huge grammar with a lot of production rules, have a lot of options.
bool deamer::LanguageDefinitionAnalyzer::DoesTokenHaveEmptyRecursion() const
{
	return false;
}
