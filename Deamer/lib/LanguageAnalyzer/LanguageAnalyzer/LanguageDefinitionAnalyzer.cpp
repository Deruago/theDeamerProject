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

#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/LanguageDefinitionAnalyzer.h"

#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/RuleAnalyzer.h"

deamer::LanguageDefinitionAnalyzer::LanguageDefinitionAnalyzer(const LanguageDefinition& languageDefinition_) : languageDefinition(languageDefinition_)
{
}

deamer::Token* deamer::LanguageDefinitionAnalyzer::GetStartToken() const
{
	if (languageDefinition.StartType != nullptr)
		return languageDefinition.StartType;
	else
		if (languageDefinition.GetTypes().empty())
			return nullptr;
		else
			return languageDefinition.GetTypes()[0];
}

bool deamer::LanguageDefinitionAnalyzer::DoesLanguageHaveEmptyRecursion() const
{
	for(auto* type : languageDefinition.GetTypes())
	{
		if (DoesTokenHaveEmptyRecursion(*type))
		{
			return true;
		}
	}

	return false;
}

// This is done by finding a cycle from NT a to NT a, via NT's.
// The analysis is extremely complex as a huge grammar with a lot of production rules, have a lot of options.
bool deamer::LanguageDefinitionAnalyzer::DoesTokenHaveEmptyRecursion(Type& type) const
{
	if (!IsTokenViableForEmptyRecursion(type))
	{
		return false;
	}

	return CheckIfTypeHasEmptyRecursion(type);
}

bool deamer::LanguageDefinitionAnalyzer::CheckIfTypeHasEmptyRecursion(deamer::Type& type) const
{
	bool lastRuleHadDoubleType = false;
	bool lastRuleHadDirectlyReferingType = false;
	for (auto i = 0; i < type.Rules.size(); i++)
	{
		const bool currentRuleHasDoubleType = DoesTypeHaveProductionRuleWhenReducedHasDoubleType(type, *type.Rules[i]);
		const bool currentRuleIsDirectlyReferingItself = DoesTypeHaveProductionRuleDirectlyReferingItself(type, *type.Rules[i]);
		if (!currentRuleHasDoubleType && !currentRuleIsDirectlyReferingItself)
		{
			return false;
		}

		if ((lastRuleHadDoubleType && currentRuleIsDirectlyReferingItself)
			|| (lastRuleHadDirectlyReferingType && currentRuleHasDoubleType))
		{
			return true;
		}

		if (currentRuleHasDoubleType)
		{
			lastRuleHadDoubleType = true;
		}

		if (currentRuleIsDirectlyReferingItself)
		{
			lastRuleHadDirectlyReferingType = true;
		}
	}
	return false;
}

// assert it has >= 2 production rules
// assert it doesn't have a defined value before a non terminal production rule
bool deamer::LanguageDefinitionAnalyzer::IsTokenViableForEmptyRecursion(Type& type) const
{
	return (type.Rules.size() >= 2);
}

bool deamer::LanguageDefinitionAnalyzer::DoesTypeHaveProductionRuleDirectlyReferingItself(const Type& type) const
{
	for (const auto* productionRule : type.Rules)
	{
		if (DoesTypeHaveProductionRuleDirectlyReferingItself(type, *productionRule))
		{
			return true;
		}
	}
	return false;
}

bool deamer::LanguageDefinitionAnalyzer::DoesTypeHaveProductionRuleDirectlyReferingItself(const Type& type, const Rule& rule) const
{
	if (rule.Tokens.size() != 1
		|| rule.Tokens[0]->IsTerminal())
	{
		return false;
	}

	if (rule.Tokens[0] == &type)
	{
		return true;
	}
	
	auto* currentType = static_cast<Type*>(rule.Tokens[0]);
	if (currentType->Rules.empty())
	{
		return false;
	}
	
	return DoesTypeHaveProductionRuleDirectlyReferingItself(type, *currentType->Rules[0]);
}

bool deamer::LanguageDefinitionAnalyzer::DoesTypeHaveProductionRuleWhenReducedHasDoubleType(const Type& type) const
{
	for (const auto* productionRule : type.Rules)
	{
		if (DoesTypeHaveProductionRuleWhenReducedHasDoubleType(type, *productionRule))
		{
			return true;
		}
	}
	return false;
}

// Assert the production rule doesn't have the following order, when completely reduced:
//		... NT1 NT1 ...
bool deamer::LanguageDefinitionAnalyzer::DoesTypeHaveProductionRuleWhenReducedHasDoubleType(const Type& type, const Rule& rule) const
{
	const auto ruleAnalyzer = RuleAnalyzer();
	const auto flattenedRule = ruleAnalyzer.FlattenRule(rule, type);
	
	return ruleAnalyzer.DoesRuleHaveMultipleCallsToTypeDirectlyAfterEachOther(flattenedRule, type);
}
