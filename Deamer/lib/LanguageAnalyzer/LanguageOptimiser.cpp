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

#include "Deamer/LanguageAnalyzer/LanguageOptimiser.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"

void deamer::LanguageOptimiser::ApplyAllOptimisations(LanguageDefinition& language_definition) const
{
	RemovedUnusedProductionRules(language_definition);
	ApplyEmptyTypeToAllEmptyRules(language_definition);
	ApplyGroupedTypeToAllGroupableRules(language_definition);
}

void deamer::LanguageOptimiser::RemovedUnusedProductionRules(LanguageDefinition& language_definition) const
{
	for (Type* type : language_definition.GetTypes())
	{
		if (!IsTypeUsedByOtherTypes(type))
			RecursivelyRemoveTypeFromLanguageDefinitionIncludingAllRules(type, language_definition);
	}
}

bool deamer::LanguageOptimiser::IsTypeUsedByOtherTypes(Type* type) const
{
	return type->TotalAmountOfTypesThatUsesThisToken >= 1;
}

void deamer::LanguageOptimiser::RecursivelyRemoveTypeFromLanguageDefinitionIncludingAllRules(Type* type, LanguageDefinition& language_definition) const
{
	language_definition.RemoveType(type);
}

void deamer::LanguageOptimiser::ApplyEmptyTypeToAllEmptyRules(LanguageDefinition& language_definition) const
{
	for (Rule* rule : language_definition.GetRules())
	{
		if (rule->Tokens.empty())
			rule->RuleType.set_flag(RuleType_t::empty);
	}
}

void deamer::LanguageOptimiser::ApplyVectorisedTypeToAllRecursiveContinuedRules(
	LanguageDefinition& language_definition) const
{
	for (Type* type : language_definition.GetTypes())
	{
		for (Rule* rule : type->Rules)
		{
			if (RuleContinuesRecursively(type, rule))
			{
				rule->RuleType.set_flag(RuleType_t::vectorised);
				type->TokenType.set_flag(TokenType_t::vector);
				type->SetBaseGroupTokensIsVector(true);
			}
		}
	}
}


bool deamer::LanguageOptimiser::RuleContinuesRecursively(Type* outputTokenOfRule, Rule* rule) const
{
	if (rule->Tokens.empty())
		return false;
	return rule->Tokens[0] == outputTokenOfRule || rule->Tokens[rule->Tokens.size() - 1] == outputTokenOfRule;
}

bool deamer::LanguageOptimiser::IsARuleInTypeAVector(Type* type) const
{
	for (Rule* rule : type->Rules)
		if (rule->Tokens[0]->TokenType.has_flag(TokenType_t::vector))
			return true;
	return false;
}

void deamer::LanguageOptimiser::ApplyGroupedTypeToAllGroupableRules(LanguageDefinition& language_definition) const
{
	for (Type* type : language_definition.GetTypes())
	{
		if (AllRulesOfTypeAreGroupable(type))
		{
			GroupAllRulesOfType(type);
			if (IsARuleInTypeAVector(type))
			{
				type->TokenType.set_flag(TokenType_t::vector);
				type->SetBaseGroupTokensIsVector(true);
			}
		}
	}
}


bool deamer::LanguageOptimiser::AllRulesOfTypeAreGroupable(Type* type) const
{
	for (Rule* rule : type->Rules)
	{
		if (!RuleIsGroupable(rule))
			return false;
	}
	return true;
}

bool deamer::LanguageOptimiser::RuleIsGroupable(Rule* rule) const
{
	return rule->Tokens.size() == 1;
}

void deamer::LanguageOptimiser::GroupAllRulesOfType(Type* type) const
{
	type->TokenType |= TokenType_t::grouped;
	for (Rule* rule : type->Rules)
	{
		rule->RuleType.set_flag(RuleType_t::grouped);
		rule->Tokens[0]->BaseTokens.push_back(type); // Sets the base type of this subtyped token
		rule->Tokens[0]->BaseGroupTokens.push_back(type); // Sets the grouped type of this subtyped token
	}
}
