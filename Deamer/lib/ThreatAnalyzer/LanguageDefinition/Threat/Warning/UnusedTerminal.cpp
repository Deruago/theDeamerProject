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

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Warning/UnusedTerminal.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::UnusedTerminal(const LanguageDefinition& languageDefinition_) : WarningThreat(id, languageDefinition_)
{
	SetThreatDescription(description);
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::warning::UnusedTerminal::
AnalyseLanguageDefinition()
{
	Token* startnode = LanguageDefinitionAnalyzer(languageDefinition).GetStartToken();
	if (startnode == nullptr)
		return {};

	dispatch(*startnode);

	std::vector<ThreatData> data;
	for (auto* node : languageDefinition.GetNodes())
	{
		if (TerminalIsInVisitedNodes(node) ||
			node->TokenPermission.has_flag(TokenPermission_t::delete_))
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