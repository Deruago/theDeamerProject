/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/ThreatData/CodeDescription/ProductionRuleCodeDescription.h"

deamer::threat::ProductionRuleCodeDescription::ProductionRuleCodeDescription(
	std::vector<TokenCodeDescription*> tokenDescriptions, std::string description, bool completeProductionRule,
	CodeDescriptionType type)
{
	TokenDescriptions = tokenDescriptions;
	Description = description;
	CompleteProductionRule = completeProductionRule;
	Type = type;
}
