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
