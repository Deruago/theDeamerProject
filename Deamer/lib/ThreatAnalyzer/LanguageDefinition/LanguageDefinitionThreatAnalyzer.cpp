/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefinitionThreatAnalyzer.h"

deamer::threat::analyzer::languagedefinition::LanguageDefinitionThreatAnalyzer::~LanguageDefinitionThreatAnalyzer()
{
	for(auto threat : Threats)
	{
		delete threat;
	}
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::LanguageDefinitionThreatAnalyzer::
AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition) const
{
	return AnalyseLanguageDefinition(languageDefinition, {});
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::LanguageDefinitionThreatAnalyzer::
AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition,
	const std::vector<LanguageDefinitionThreat>& skippedThreatPasses) const
{
	std::vector<ThreatData> threatData;

	for (auto threat : Threats)
	{
		if (ThreatIsInSkippedThreatPasses(threat, skippedThreatPasses))
			continue;
		
		const auto data_ = threat->AnalyseLanguageDefinition(languageDefinition);
		for (const auto& threatData_ : data_)
		{
			threatData.push_back(threatData_);
		}
	}

	return threatData;
}

bool deamer::threat::analyzer::languagedefinition::LanguageDefinitionThreatAnalyzer::ThreatIsInSkippedThreatPasses(
	Threat* threat, const std::vector<LanguageDefinitionThreat>& skippedPasses) const
{
	for (const auto& skippedPass : skippedPasses)
	{
		if (threat->threatData.ThreatId == static_cast<unsigned>(skippedPass))
			return true;
	}
	return false;
}
