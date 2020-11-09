/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/ThreatData/ErrorThreatData.h"
#include "Deamer/ThreatAnalyzer/ThreatType.h"

deamer::threat::ErrorThreatData::ErrorThreatData(const std::string& description, const unsigned id) : ThreatData(ThreatType::error, description, id)
{
}
