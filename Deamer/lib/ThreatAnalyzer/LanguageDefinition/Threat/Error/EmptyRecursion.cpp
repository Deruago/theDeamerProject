/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/EmptyRecursion.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::EmptyRecursion() : ErrorThreat(id)
{
	SetThreatDescription(description);
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::
AnalyseLanguageDefinition(const LanguageDefinition & languageDefinition)
{
	languageDefinition_ = languageDefinition;
	Token* startType = LanguageDefinitionAnalyzer(languageDefinition).GetStartToken();
	if (startType == nullptr)
		return {};

	dispatch(*startType);

	std::vector<ThreatData> data;
	for (auto* type : languageDefinition.Types)
	{
		if (NonTerminalIsInVisitedTypes(type))
			continue;

		data.push_back(MakeThreatData(type));
	}
	return data;
}

deamer::threat::ThreatData deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::MakeThreatData(Type * type) const
{
	ThreatData newThreatData = threatData;
	const auto specializedThreatDescription = description + " '" + type->TokenName + "'";
	newThreatData.SetDescription(specializedThreatDescription);

	const auto codeDescription = MakeThreatCodeDescription(type);
	newThreatData.SetCodeDescription(codeDescription);

	return newThreatData;
}

deamer::threat::ThreatCodeDescription deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::
MakeThreatCodeDescription(Type * type) const
{
	auto description = ThreatCodeDescription(type, type);
	const auto tokenDescription = TokenCodeDescription(type, MakeErrorDescription(*type), CodeDescriptionType::error);
	description.TokenCodeDescriptions.push_back(tokenDescription);
	return description;
}

std::string deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::MakeErrorDescription(const Type & type) const
{
	return "Non terminal: '" + type.TokenName + "' has empty recursion";
}

bool deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::NonTerminalIsInVisitedTypes(Type * type) const
{
	for (auto* used_type : UsedTypes)
		if (used_type == type)
			return true;

	return false;
}

void deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::first_visit(Type & visited_type)
{

	if (!LanguageDefinitionAnalyzer(languageDefinition_).DoesTokenHaveEmptyRecursion())
	{
		UsedTypes.push_back(&visited_type);	
	}
}

void deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::first_visit(Rule & visited_type) { }
void deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::first_visit(Node & visited_type) { }
void deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::visit(Type & type) { }
void deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::visit(Node & node) { }