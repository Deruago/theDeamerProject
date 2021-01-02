/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
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
