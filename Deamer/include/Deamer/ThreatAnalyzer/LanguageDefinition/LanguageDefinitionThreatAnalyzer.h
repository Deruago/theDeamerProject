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
#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefintionThreat.h"

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition {
	
	class LanguageDefinitionThreatAnalyzer final : public ThreatAnalyzer
	{
	private:
		const LanguageDefinition& languageDefinition;
		const std::vector<Threat*> Threats;
		
		bool ThreatIsInSkippedThreatPasses(Threat* threat, const std::vector<LanguageDefinitionThreat>& skippedPasses) const;
	public:
		LanguageDefinitionThreatAnalyzer(const LanguageDefinition& languageDefinition_);
		~LanguageDefinitionThreatAnalyzer() override;
		
		std::vector<ThreatData> AnalyseLanguageDefinition() const;
		std::vector<ThreatData> AnalyseLanguageDefinition(const std::vector<LanguageDefinitionThreat>& skippedThreatPasses) const;
	};

}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_LANGUAGEDEFINITIONTHREATANALYZER_H