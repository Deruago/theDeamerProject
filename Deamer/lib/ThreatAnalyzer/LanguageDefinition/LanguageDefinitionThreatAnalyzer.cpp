/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefinitionThreatAnalyzer.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/MultipleDeclarationTerminal.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/MultipleDeclarationNonTerminal.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/MultipleDeclarationProductionRule.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/NonTerminalHasNoProductionRulesAssociated.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/EmptyRecursion.h"

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/NoStartingSymbolSpecified.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/UnusedProductionRule.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/UnusedTerminal.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/UnusedNonTerminal.h"

deamer::threat::analyzer::languagedefinition::LanguageDefinitionThreatAnalyzer::LanguageDefinitionThreatAnalyzer(const LanguageDefinition& languageDefinition_)
		:	languageDefinition(languageDefinition_),
			Threats(
				{
					new error::EmptyRecursion(languageDefinition_),
					new error::MultipleDeclarationTerminal(languageDefinition_),
					new error::MultipleDeclarationNonTerminal(languageDefinition_),
					new error::MultipleDeclarationProductionRule(languageDefinition_),
					new error::NonTerminalHasNoProductionRulesAssociated(languageDefinition_),

					new warning::NoStartingSymbolSpecified(languageDefinition_),
					new warning::UnusedProductionRule(languageDefinition_),
					new warning::UnusedTerminal(languageDefinition_),
					new warning::UnusedNonTerminal(languageDefinition_),
				}
			)
{
}

deamer::threat::analyzer::languagedefinition::LanguageDefinitionThreatAnalyzer::~LanguageDefinitionThreatAnalyzer()
{
	for(auto* threat : Threats)
	{
		delete threat;
	}
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::LanguageDefinitionThreatAnalyzer::
AnalyseLanguageDefinition() const
{
	return AnalyseLanguageDefinition({});
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::LanguageDefinitionThreatAnalyzer::
AnalyseLanguageDefinition(const std::vector<LanguageDefinitionThreat>& skippedThreatPasses) const
{
	std::vector<ThreatData> threatData;

	for (auto* threat : Threats)
	{
		if (ThreatIsInSkippedThreatPasses(threat, skippedThreatPasses))
			continue;
		
		const auto data_ = threat->AnalyseLanguageDefinition();
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
