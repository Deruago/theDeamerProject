/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/UnusedNonTerminal.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

deamer::threat::analyzer::languagedefinition::warning::UnusedNonTerminal::UnusedNonTerminal() : WarningThreat(id)
{
	SetThreatDescription(description);
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::warning::UnusedNonTerminal::
AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition)
{
	Token* startType = LanguageDefinitionAnalyzer(languageDefinition).GetStartToken();
	if (startType == nullptr)
		return {};

	dispatch(*startType);

	std::vector<ThreatData> data;
	for (auto type : languageDefinition.Types)
	{
		if (NonTerminalIsInVisitedTypes(type))
			continue;
		
		data.push_back(MakeThreatData(type));
	}
	return data;
}

deamer::threat::ThreatData deamer::threat::analyzer::languagedefinition::warning::UnusedNonTerminal::MakeThreatData(Type* type) const
{
	ThreatData newThreatData = threatData;
	const auto specializedThreatDescription = description + " '" + type->TokenName + "'";
	newThreatData.SetDescription(specializedThreatDescription);
	
	const auto codeDescription = MakeThreatCodeDescription(type);
	newThreatData.SetCodeDescription(codeDescription);
	
	return newThreatData;
}

deamer::threat::ThreatCodeDescription deamer::threat::analyzer::languagedefinition::warning::UnusedNonTerminal::
MakeThreatCodeDescription(Type* type) const
{
	auto description = ThreatCodeDescription(type, type);
	const auto tokenDescription = TokenCodeDescription(type, MakeErrorDescription(*type), CodeDescriptionType::warning);
	description.TokenCodeDescriptions.push_back(tokenDescription);
	return description;
}

std::string deamer::threat::analyzer::languagedefinition::warning::UnusedNonTerminal::MakeErrorDescription(const Type& type) const
{
	return "Non terminal: '" + type.TokenName + "' is not used.";
}

bool deamer::threat::analyzer::languagedefinition::warning::UnusedNonTerminal::NonTerminalIsInVisitedTypes(Type* type) const
{
	for (auto used_type : UsedTypes)
		if (used_type == type)
			return true;

	return false;
}

void deamer::threat::analyzer::languagedefinition::warning::UnusedNonTerminal::first_visit(Type& visited_type)
{
	UsedTypes.push_back(&visited_type);
}

void deamer::threat::analyzer::languagedefinition::warning::UnusedNonTerminal::first_visit(Rule& visited_type) { }
void deamer::threat::analyzer::languagedefinition::warning::UnusedNonTerminal::first_visit(Node& visited_type) { }
void deamer::threat::analyzer::languagedefinition::warning::UnusedNonTerminal::visit(Type& type) { }
void deamer::threat::analyzer::languagedefinition::warning::UnusedNonTerminal::visit(Node& node) { }