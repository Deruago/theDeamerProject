/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/LanguageAnalyzer/LanguageAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LanguageGen/Rule.h"
#include "Deamer/LanguageGen/Type.h"

void deamer::LanguageAnalyzer::ApplyAllOptimisations(LanguageDefinition& language_definition) const
{
	RemovedUnusedProductionRules(language_definition);
	ApplyEmptyTypeToAllEmptyRules(language_definition);
	ApplyGroupedTypeToAllGroupableRules(language_definition);
}

void deamer::LanguageAnalyzer::RemovedUnusedProductionRules(LanguageDefinition& language_definition) const
{
	for(Type* type : language_definition.Types)
	{
		if (!IsTypeUsedByOtherTypes(type))
			RecursivelyRemoveTypeFromLanguageDefinitionIncludingAllRules(type, language_definition);
	}
}

bool deamer::LanguageAnalyzer::IsTypeUsedByOtherTypes(Type* type) const
{
	return type->TotalAmountOfTypesThatUsesThisToken >= 1;
}

void deamer::LanguageAnalyzer::RecursivelyRemoveTypeFromLanguageDefinitionIncludingAllRules(Type* type, LanguageDefinition& language_definition) const
{
	language_definition.RemoveType(type);
}

void deamer::LanguageAnalyzer::ApplyEmptyTypeToAllEmptyRules(LanguageDefinition& language_definition) const
{
	for (Rule* rule : language_definition.Rules)
	{
		if(rule->IsEmpty())
			rule->RuleType = RuleType_t::empty;
	}
}

void deamer::LanguageAnalyzer::ApplyVectorisedTypeToAllRecursiveContinuedRules(
	LanguageDefinition& language_definition) const
{
	for(Type* type : language_definition.Types)
	{
		for(Rule* rule : type->Rules)
		{
			if(RuleContinuesRecursively(type, rule))
				rule->RuleType = RuleType_t::vectorised;
		}
	}
}


bool deamer::LanguageAnalyzer::RuleContinuesRecursively(Type* outputTokenOfRule, Rule* rule) const
{
	if (rule->Tokens[0] == outputTokenOfRule || rule->Tokens[rule->Tokens.size()] == outputTokenOfRule)
		return true;
	return false;
}

void deamer::LanguageAnalyzer::ApplyGroupedTypeToAllGroupableRules(LanguageDefinition& language_definition) const
{
	for(Type* type : language_definition.Types)
	{
		if (AllRulesOfTypeAreGroupable(type))
			GroupAllRulesOfType(type);
	}
}


bool deamer::LanguageAnalyzer::AllRulesOfTypeAreGroupable(Type* type) const
{
	for(Rule* rule : type->Rules)
	{
		if (!RuleIsGroupable(rule))
			return false;
	}
	return true;
}

bool deamer::LanguageAnalyzer::RuleIsGroupable(Rule* rule) const
{
	return rule->Tokens.size() == 1;
}

void deamer::LanguageAnalyzer::GroupAllRulesOfType(Type* type) const
{
	type->GroupedType = true;
	for(Rule* rule : type->Rules)
	{
		rule->RuleType = RuleType_t::grouped;
	}
}