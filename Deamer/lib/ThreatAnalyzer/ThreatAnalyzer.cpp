/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/ThreatAnalyzer.h"
#include "Deamer/ThreatAnalyzer/ThreatType.h"

bool deamer::threat::ThreatAnalyzer::DoesThreatDataContainErrors(const std::vector<ThreatData>& threatData) const
{
	for (const auto& threatData_ : threatData)
	{
		if (threatData_.Type == ThreatType::error)
			return true;
	}
	return false;
}

bool deamer::threat::ThreatAnalyzer::DoesThreatDataContainWarnings(const std::vector<ThreatData>& threatData) const
{
	for (const auto& threatData_ : threatData)
	{
		if (threatData_.Type == ThreatType::warning)
			return true;
	}
	return false;
}
