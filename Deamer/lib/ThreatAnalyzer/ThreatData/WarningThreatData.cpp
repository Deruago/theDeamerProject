/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/ThreatData/WarningThreatData.h"
#include "Deamer/ThreatAnalyzer/ThreatType.h"

deamer::threat::WarningThreatData::WarningThreatData(const std::string& description, const unsigned id) : ThreatData(ThreatType::error, description, id)
{
}
