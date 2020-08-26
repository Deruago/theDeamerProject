/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/LanguageGen/RuleFactory.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"

deamer::Rule* deamer::RuleFactory::MakeRule() const
{
	Rule* new_rule = new Rule();
	new_rule->RuleType.set_flag(RuleType_t::empty);
	return new_rule;
}

deamer::Rule* deamer::RuleFactory::MakeRule(Token* token) const
{
	return new Rule({ token });
}

deamer::Rule* deamer::RuleFactory::MakeRule(const std::vector<deamer::Token*>& tokens) const
{
	Rule* new_rule = new Rule(tokens);
	if (tokens.empty())
		new_rule->RuleType.set_flag(RuleType_t::empty);
	return new_rule;
}

deamer::Rule* deamer::RuleFactory::MakeGroupedRule(Token* token) const
{
	Rule* new_grouped_rule = new Rule({ token });
	new_grouped_rule->RuleType.set_flag(RuleType_t::grouped);
	return new_grouped_rule;
}

deamer::Rule* deamer::RuleFactory::MakeEmptyRule() const
{
	Rule* new_empty_rule = new Rule();
	new_empty_rule->RuleType.set_flag(RuleType_t::empty);
	return new_empty_rule;
}

deamer::Rule* deamer::RuleFactory::MakeDefaultRule(const std::vector<Token*>& tokens)
{
	return new Rule(tokens);
}

