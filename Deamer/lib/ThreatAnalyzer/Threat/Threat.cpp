/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/Threat/Threat.h"

deamer::threat::Threat::Threat(ThreatType type, unsigned threatId, const LanguageDefinition& languageDefinition_) : languageDefinition(languageDefinition_)
{
	threatData = ThreatData(type, "", threatId);
}

void deamer::threat::Threat::SetThreatDescription(const std::string& description)
{
	threatData.SetDescription(description);
}
