/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/UnusedProductionRule.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::UnusedProductionRule() : WarningThreat(id)
{
	SetThreatDescription(description);
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::
AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition)
{
	Token* startType = LanguageDefinitionAnalyzer(languageDefinition).GetStartToken();
	if (startType == nullptr)
		return {};

	dispatch(*startType);

	std::vector<ThreatData> data;
	for (auto* rule : languageDefinition.GetRules())
	{
		if (ProductionRuleIsInVisitedRules(rule))
			continue;

		data.push_back(MakeThreatData(rule));
	}
	return data;
}

deamer::threat::ThreatData deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::MakeThreatData(Rule* rule) const
{
	ThreatData newThreatData = threatData;
	const auto codeDescription = MakeThreatCodeDescription(rule);
	newThreatData.SetCodeDescription(codeDescription);

	return newThreatData;
}

deamer::threat::ThreatCodeDescription deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::
MakeThreatCodeDescription(Rule* rule) const
{
	auto description = ThreatCodeDescription(nullptr, nullptr);
	const auto productionruleDescription = ProductionRuleCodeDescription({}, MakeErrorDescription(*rule), true, CodeDescriptionType::warning);
	description.ProductionCodeDescriptions.push_back(productionruleDescription);
	return description;
}

std::string deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::MakeErrorDescription(const Rule& rule) const
{
	return "";
}

bool deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::ProductionRuleIsInVisitedRules(Rule* rule) const
{
	for (auto used_rule : UsedRules)
		if (used_rule == rule)
			return true;

	return false;
}

void deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::first_visit(Type& visited_type) { }
void deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::first_visit(Rule& visited_type)
{
	UsedRules.push_back(&visited_type);
}
void deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::first_visit(Node& visited_type) { }
void deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::visit(Type& type) { }
void deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::visit(Node& node) { }