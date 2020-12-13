/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/MultipleDeclarationNonTerminal.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::MultipleDeclarationNonTerminal(const LanguageDefinition& languageDefinition_) : ErrorThreat(id, languageDefinition_)
{
	SetThreatDescription(description);
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::
AnalyseLanguageDefinition()
{
	Token* startType = LanguageDefinitionAnalyzer(languageDefinition).GetStartToken();
	if (startType == nullptr)
		return {};

	dispatch(*startType);

	std::vector<ThreatData> data;
	for (auto type : DuplicateType)
	{
		data.push_back(MakeThreatData(type));
	}
	return data;
}

deamer::threat::ThreatData deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::MakeThreatData(Type* type) const
{
	ThreatData newThreatData = threatData;
	const auto specializedThreatDescription = description + " '" + type->TokenName + "'";
	newThreatData.SetDescription(specializedThreatDescription);

	const auto codeDescription = MakeThreatCodeDescription(type);
	newThreatData.SetCodeDescription(codeDescription);

	return newThreatData;
}

deamer::threat::ThreatCodeDescription deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::
MakeThreatCodeDescription(Type* type) const
{
	auto description = ThreatCodeDescription(type, type);
	const auto tokenDescription = TokenCodeDescription(type, MakeErrorDescription(*type), CodeDescriptionType::error);
	description.TokenCodeDescriptions.push_back(tokenDescription);
	return description;
}

std::string deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::MakeErrorDescription(const Type& type) const
{
	return "Non terminal: '" + type.TokenName + "' is redeclared";
}

bool deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::
NonTerminalHasSameNameAsOtherNonTerminal(const Type* a, const Type* b) const
{
	return a->TokenName == b->TokenName;
}

bool deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::
NonTerminalHasSameNameAsAnyOfAlreadyVisitedTypes(const Type* type) const
{
	for (auto used_type : UsedTypes)
		if (NonTerminalHasSameNameAsOtherNonTerminal(type, used_type))
			return true;
	
	return false;
}

bool deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::NonTerminalIsInVisitedTypes(Type* type) const
{
	for (auto used_type : UsedTypes)
		if (used_type == type)
			return true;

	return false;
}

bool deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::
NonTerminalIsInDuplicatedTypes(const Type* type) const
{
	for (auto duplicated_type : DuplicateType)
		if (duplicated_type == type)
			return true;

	return false;
}

void deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::first_visit(Type& visited_type)
{
	if (NonTerminalHasSameNameAsAnyOfAlreadyVisitedTypes(&visited_type) && !NonTerminalIsInDuplicatedTypes(&visited_type))
		DuplicateType.push_back(&visited_type);
	else
		UsedTypes.push_back(&visited_type);
}

void deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::first_visit(Rule& visited_type) { }
void deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::first_visit(Node& visited_type) { }
void deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::visit(Type& type) { }
void deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationNonTerminal::visit(Node& node) { }