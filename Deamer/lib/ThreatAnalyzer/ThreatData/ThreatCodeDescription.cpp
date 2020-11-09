/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/ThreatData/ThreatCodeDescription.h"

deamer::threat::ThreatCodeDescription::ThreatCodeDescription()
{
	Entry = nullptr;
	End = nullptr;
}

deamer::threat::ThreatCodeDescription::ThreatCodeDescription(Token* entry, Token* end)
{
	Entry = entry;
	End = end;
}

void deamer::threat::ThreatCodeDescription::AddTokenCodeDescription(TokenCodeDescription& tokenCodeDescription)
{
	TokenCodeDescriptions.push_back(tokenCodeDescription);
}

void deamer::threat::ThreatCodeDescription::AddProductionruleDescription(
	ProductionRuleCodeDescription& productionRuleCodeDescription)
{
	ProductionCodeDescriptions.push_back(productionRuleCodeDescription);
}
