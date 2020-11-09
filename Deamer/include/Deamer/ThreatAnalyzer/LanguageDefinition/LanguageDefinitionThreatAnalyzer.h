/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_LANGUAGEDEFINITION_LANGUAGEDEFINITIONTHREATANALYZER_H
#define DEAMER_THREATANALYZER_LANGUAGEDEFINITION_LANGUAGEDEFINITIONTHREATANALYZER_H

#include "Deamer/ThreatAnalyzer/Threat/Threat.h"
#include "Deamer/ThreatAnalyzer/ThreatAnalyzer.h"

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/MultipleDeclarationTerminal.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/MultipleDeclarationNonTerminal.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/MultipleDeclarationProductionRule.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/NonTerminalHasNoProductionRulesAssociated.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/EmptyRecursion.h"

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/NoStartingSymbolSpecified.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/UnusedProductionRule.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/UnusedTerminal.h"
#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/UnusedNonTerminal.h"

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition {
	
	class LanguageDefinitionThreatAnalyzer final : public ThreatAnalyzer
	{
	private:
		const std::vector<Threat*> Threats = {
			new error::EmptyRecursion(),
			new error::MultipleDeclarationTerminal(),
			new error::MultipleDeclarationNonTerminal(),
			new error::MultipleDeclarationProductionRule(),
			new error::NonTerminalHasNoProductionRulesAssociated(),
			
			new warning::NoStartingSymbolSpecified(),
			new warning::UnusedProductionRule(),
			new warning::UnusedTerminal(),
			new warning::UnusedNonTerminal(),
		};
		bool ThreatIsInSkippedThreatPasses(Threat* threat, const std::vector<LanguageDefinitionThreat>& skippedPasses) const;
	public:
		LanguageDefinitionThreatAnalyzer() = default;
		~LanguageDefinitionThreatAnalyzer() override;
		
		std::vector<ThreatData> AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition) const override;
		std::vector<ThreatData> AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition, const std::vector<LanguageDefinitionThreat>& skippedThreatPasses) const;
	};

}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_LANGUAGEDEFINITIONTHREATANALYZER_H