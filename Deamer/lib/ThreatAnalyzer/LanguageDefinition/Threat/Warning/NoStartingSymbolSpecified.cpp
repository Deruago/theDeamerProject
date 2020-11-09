/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/NoStartingSymbolSpecified.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

deamer::threat::analyzer::languagedefinition::warning::NoStartingSymbolSpecified::NoStartingSymbolSpecified() : WarningThreat(id)
{
	SetThreatDescription(description);
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::warning::NoStartingSymbolSpecified::
AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition)
{
	if (languageDefinition.StartType == nullptr)
		return {threatData};
	else
		return {};
}
