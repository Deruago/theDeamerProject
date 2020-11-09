/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/UnusedTerminal.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::UnusedTerminal() : WarningThreat(id)
{
	SetThreatDescription(description);
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::
AnalyseLanguageDefinition(const LanguageDefinition & languageDefinition)
{
	Token* startnode = LanguageDefinitionAnalyzer(languageDefinition).GetStartToken();
	if (startnode == nullptr)
		return {};

	dispatch(*startnode);

	std::vector<ThreatData> data;
	for (auto node : languageDefinition.Nodes)
	{
		if (TerminalIsInVisitedNodes(node))
			continue;

		data.push_back(MakeThreatData(node));
	}
	return data;
}

deamer::threat::ThreatData deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::MakeThreatData(Node* node) const
{
	ThreatData newThreatData = threatData;
	const auto specializedThreatDescription = description + " '" + node->TokenName + "'";
	newThreatData.SetDescription(specializedThreatDescription);

	const auto codeDescription = MakeThreatCodeDescription(node);
	newThreatData.SetCodeDescription(codeDescription);

	return newThreatData;
}

deamer::threat::ThreatCodeDescription deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::
MakeThreatCodeDescription(Node* node) const
{
	auto description = ThreatCodeDescription(node, node);
	const auto tokenDescription = TokenCodeDescription(node, MakeErrorDescription(*node), CodeDescriptionType::warning);
	description.TokenCodeDescriptions.push_back(tokenDescription);
	return description;
}

std::string deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::MakeErrorDescription(const Node& node) const
{
	return "Terminal: '" + node.TokenName + "' is not used.";
}

bool deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::TerminalIsInVisitedNodes(Node* node) const
{
	for (auto used_node : UsedNodes)
		if (used_node == node)
			return true;

	return false;
}

void deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::first_visit(Node& visited_type)
{
	UsedNodes.push_back(&visited_type);
}

void deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::first_visit(Rule& visited_type) { }
void deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::first_visit(Type& visited_type) { }
void deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::visit(Type& type) { }
void deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::visit(Node& node) { }