/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/ThreatData/ThreatData.h"

deamer::threat::ThreatData::ThreatData(const ThreatType type, const std::string& threatDescription, const unsigned threatId)
{
	Type = type;
	ThreatId = threatId;
	SetDescription(threatDescription);
	CodeDescription = ThreatCodeDescription();
}

void deamer::threat::ThreatData::SetDescription(const std::string& threatDescription)
{
	ThreatDescription = threatDescription;
}

void deamer::threat::ThreatData::SetCodeDescription(const ThreatCodeDescription& threatCodeDescription)
{
	CodeDescription = threatCodeDescription;
}
