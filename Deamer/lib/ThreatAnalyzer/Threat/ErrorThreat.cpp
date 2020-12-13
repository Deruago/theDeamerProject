/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/Threat/ErrorThreat.h"
#include "Deamer/ThreatAnalyzer/ThreatType.h"

deamer::threat::ErrorThreat::ErrorThreat(const unsigned id, const LanguageDefinition& languageDefinition) : Threat(ThreatType::error, id, languageDefinition)
{
}
