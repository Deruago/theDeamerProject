/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/EmptyRecursion.h"

deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::EmptyRecursion() : ErrorThreat(id)
{
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::
AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition)
{
	return {};
}
