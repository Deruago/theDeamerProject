/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONPRODUCTIONRULE_H
#define DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONPRODUCTIONRULE_H

#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefintionThreat.h"
#include "Deamer/ThreatAnalyzer/Threat/ErrorThreat.h"

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition { namespace error {

	class MultipleDeclarationProductionRule : public ErrorThreat
	{
	public:
		const std::string description = "No starting symbol specified";
		constexpr static unsigned id = static_cast<unsigned>(LanguageDefinitionThreat::multipleDeclarationProductionRule);
		MultipleDeclarationProductionRule();

		std::vector<ThreatData> AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition) override;
	};

}}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONPRODUCTIONRULE_H