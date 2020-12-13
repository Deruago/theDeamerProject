/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/MultipleDeclarationTerminal.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::MultipleDeclarationTerminal(const LanguageDefinition& languageDefinition) : ErrorThreat(id, languageDefinition)
{
	SetThreatDescription(description);
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::
AnalyseLanguageDefinition()
{
	Token* startType = LanguageDefinitionAnalyzer(languageDefinition).GetStartToken();
	if (startType == nullptr)
		return {};

	dispatch(*startType);

	std::vector<ThreatData> data;
	for (auto node : DuplicateNodes)
	{
		data.push_back(MakeThreatData(node));
	}
	return data;
}

deamer::threat::ThreatData deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::MakeThreatData(Node* node) const
{
	ThreatData newThreatData = threatData;
	const auto specializedThreatDescription = description + " '" + node->TokenName + "'";
	newThreatData.SetDescription(specializedThreatDescription);

	const auto codeDescription = MakeThreatCodeDescription(node);
	newThreatData.SetCodeDescription(codeDescription);

	return newThreatData;
}

deamer::threat::ThreatCodeDescription deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::
MakeThreatCodeDescription(Node* node) const
{
	auto description = ThreatCodeDescription(node, node);
	const auto tokenDescription = TokenCodeDescription(node, MakeErrorDescription(*node), CodeDescriptionType::error);
	description.TokenCodeDescriptions.push_back(tokenDescription);
	return description;
}

std::string deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::MakeErrorDescription(const Node& node) const
{
	return "Terminal: '" + node.TokenName + "' is redeclared";
}

bool deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::
NonTerminalHasSameNameAsOtherNonTerminal(const Node* a, const Node* b) const
{
	return a->TokenName == b->TokenName;
}

bool deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::
NonTerminalHasSameNameAsAnyOfAlreadyVisitedTypes(const Node* node) const
{
	for (auto used_type : UsedNodes)
		if (NonTerminalHasSameNameAsOtherNonTerminal(node, used_type))
			return true;

	return false;
}

bool deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::NonTerminalIsInVisitedTypes(Node* node) const
{
	for (auto used_node : UsedNodes)
		if (used_node == node)
			return true;

	return false;
}

bool deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::
NonTerminalIsInDuplicatedTypes(const Node * node) const
{
	for (auto duplicated_node : DuplicateNodes)
		if (duplicated_node == node)
			return true;

	return false;
}

void deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::first_visit(Node& visited_type)
{
	if (NonTerminalHasSameNameAsAnyOfAlreadyVisitedTypes(&visited_type) && !NonTerminalIsInDuplicatedTypes(&visited_type))
		DuplicateNodes.push_back(&visited_type);
	else
		UsedNodes.push_back(&visited_type);
}

void deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::first_visit(Rule& visited_type) { }
void deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::first_visit(Type& visited_type) { }
void deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::visit(Type& type) { }
void deamer::threat::analyzer::languagedefinition::error::MultipleDeclarationTerminal::visit(Node& node) { }