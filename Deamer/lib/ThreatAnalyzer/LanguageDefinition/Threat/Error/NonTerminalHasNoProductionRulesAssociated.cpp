/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/NonTerminalHasNoProductionRulesAssociated.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::
NonTerminalHasNoProductionRulesAssociated(const LanguageDefinition& languageDefinition_) : ErrorThreat(id, languageDefinition_)
{
	SetThreatDescription(description);
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::
AnalyseLanguageDefinition()
{
	Token* startType = LanguageDefinitionAnalyzer(languageDefinition).GetStartToken();
	if (startType == nullptr)
		return {};

	dispatch(*startType);

	std::vector<ThreatData> data;
	for (auto type : languageDefinition.GetTypes())
	{
		if (NonTerminalHasProductionRules(type) ||
			!NonTerminalIsInVisitedTypes(type))
			continue;

		data.push_back(MakeThreatData(type));
	}
	return data;
}

deamer::threat::ThreatData deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::MakeThreatData(Type * type) const
{
	ThreatData newThreatData = threatData;
	const auto specializedThreatDescription = description + " '" + type->TokenName + "'";
	newThreatData.SetDescription(specializedThreatDescription);

	const auto codeDescription = MakeThreatCodeDescription(type);
	newThreatData.SetCodeDescription(codeDescription);

	return newThreatData;
}

deamer::threat::ThreatCodeDescription deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::
MakeThreatCodeDescription(Type * type) const
{
	auto description = ThreatCodeDescription(type, type);
	const auto tokenDescription = TokenCodeDescription(type, MakeErrorDescription(*type), CodeDescriptionType::error);
	description.TokenCodeDescriptions.push_back(tokenDescription);
	return description;
}

std::string deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::MakeErrorDescription(const Type & type) const
{
	return "Non terminal: '" + type.TokenName + "' has no production-rules";
}

bool deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::NonTerminalHasProductionRules(const Type * type) const
{
	return !type->Rules.empty();
}


bool deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::NonTerminalIsInVisitedTypes(const Type* type) const
{
	for (auto used_type : UsedTypes)
		if (used_type == type)
			return true;

	return false;
}

void deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::first_visit(Type & visited_type)
{
	UsedTypes.push_back(&visited_type);
}

void deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::first_visit(Rule & visited_type) { }
void deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::first_visit(Node & visited_type) { }
void deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::visit(Type & type) { }
void deamer::threat::analyzer::languagedefinition::error::NonTerminalHasNoProductionRulesAssociated::visit(Node & node) { }