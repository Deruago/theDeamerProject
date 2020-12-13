/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/Threat/WarningThreat.h"
#include "Deamer/ThreatAnalyzer/ThreatType.h"

deamer::threat::WarningThreat::WarningThreat(const unsigned id, const LanguageDefinition& languageDefinition_) : Threat(ThreatType::warning, id, languageDefinition_)
{
}
