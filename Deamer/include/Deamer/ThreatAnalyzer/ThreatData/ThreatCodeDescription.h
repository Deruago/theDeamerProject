/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_THREATDATA_THREATCODEDESCRIPTION_H
#define DEAMER_THREATANALYZER_THREATDATA_THREATCODEDESCRIPTION_H

#include "Deamer/ThreatAnalyzer/ThreatData/CodeDescription/TokenCodeDescription.h"
#include "Deamer/ThreatAnalyzer/ThreatData/CodeDescription/ProductionRuleCodeDescription.h"
#include <vector>

namespace deamer {
	class Token;
}

namespace deamer { namespace threat {

	class ThreatCodeDescription
	{
	public:
		Token* Entry;
		Token* End;

		std::vector<TokenCodeDescription> TokenCodeDescriptions;
		std::vector<ProductionRuleCodeDescription> ProductionCodeDescriptions;
		
		ThreatCodeDescription();
		ThreatCodeDescription(Token* entry, Token* end);
		
		void AddTokenCodeDescription(TokenCodeDescription& tokenCodeDescription);
		void AddProductionruleDescription(ProductionRuleCodeDescription& productionRuleCodeDescription);
	};

}}

#endif //DEAMER_THREATANALYZER_THREATDATA_THREATCODEDESCRIPTION_H