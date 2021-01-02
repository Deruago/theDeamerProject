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

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/UnusedProductionRule.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::UnusedProductionRule(const LanguageDefinition& languageDefinition_) : WarningThreat(id, languageDefinition_)
{
	SetThreatDescription(description);
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::warning::UnusedProductionRule::
AnalyseLanguageDefinition()
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