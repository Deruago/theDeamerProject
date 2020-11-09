/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_PRODUCTIONRULECODEDESCRIPTION_H
#define DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_PRODUCTIONRULECODEDESCRIPTION_H

#include "Deamer/ThreatAnalyzer/ThreatData/CodeDescription/CodeDescriptionType.h"
#include <vector>
#include <string>

namespace deamer { namespace threat {
	class TokenCodeDescription;
	
	class ProductionRuleCodeDescription
	{
	public:
		std::vector<TokenCodeDescription*> TokenDescriptions;
		CodeDescriptionType Type;
		std::string Description;
		bool CompleteProductionRule;
		
		ProductionRuleCodeDescription(std::vector<TokenCodeDescription*> tokenDescriptions, std::string description, bool completeProductionRule, CodeDescriptionType type);
	};

}}

#endif //DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_PRODUCTIONRULECODEDESCRIPTION_H