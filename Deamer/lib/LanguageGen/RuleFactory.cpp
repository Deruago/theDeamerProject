/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/LanguageGen/RuleFactory.h"
#include "Deamer/LanguageGen/Rule.h"
#include "Deamer/LanguageGen/Token.h"

deamer::Rule* deamer::RuleFactory::MakeRule(Token* token) const
{
	return new Rule({ token });
}

deamer::Rule* deamer::RuleFactory::MakeRule(const std::vector<deamer::Token*>& tokens) const
{
	return new Rule(tokens);
}

deamer::Rule* deamer::RuleFactory::MakeGroupedRule(Token* token) const
{
	Rule* new_grouped_rule = new Rule({ token });
	new_grouped_rule->RuleType = RuleType_t::grouped;
	return new_grouped_rule;
}
