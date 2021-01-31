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

#include "Deamer/ThreatAnalyzer/LanguageDefinition/Threat/Error/EmptyRecursion.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::EmptyRecursion(const LanguageDefinition& languageDefinition_) : ErrorThreat(id, languageDefinition_)
{
	SetThreatDescription(description);
}

std::vector<deamer::threat::ThreatData> deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::
AnalyseLanguageDefinition()
{
	Token* startType = LanguageDefinitionAnalyzer(languageDefinition).GetStartToken();
	if (startType == nullptr)
		return {};

	dispatch(*startType);

	std::vector<ThreatData> data;
	for (auto* type : languageDefinition.GetTypes())
	{
		if (!NonTerminalIsInTypesWithEmptyRecursion(type))
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

bool deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::NonTerminalIsInTypesWithEmptyRecursion(
	Type* type) const
{
	for (auto* visited_type : TypesWithEmptyRecursion)
		if (visited_type == type)
			return true;

	return false;
}

void deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::first_visit(Type & visited_type)
{
	if (LanguageDefinitionAnalyzer(languageDefinition).DoesTokenHaveEmptyRecursion(visited_type))
	{
		TypesWithEmptyRecursion.push_back(&visited_type);
	}
	
	UsedTypes.push_back(&visited_type);
}

void deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::first_visit(Rule & visited_type) { }
void deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::first_visit(Node & visited_type) { }
void deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::visit(Type & type) { }
void deamer::threat::analyzer::languagedefinition::error::EmptyRecursion::visit(Node & node) { }