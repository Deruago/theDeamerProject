/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/RuleAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"


bool deamer::RuleAnalyzer::IsEmpty(Rule& rule) const
{
	return rule.Tokens.empty();
}

bool deamer::RuleAnalyzer::IsGroupable(Rule& rule) const
{
	return rule.Tokens.size() == 1;
}

bool deamer::RuleAnalyzer::IsVectorisable(Rule& rule) const
{
	if (rule.Tokens.empty())
		return false;
	for (Token* token : rule.Tokens)
		if (!token->TokenPermission.has_flag(TokenPermission_t::node))
			for (Rule* rule_in_type : static_cast<Type*>(token)->Rules)
				if (rule_in_type == &rule)
					return true;
	return false;
}

bool deamer::RuleAnalyzer::IsVectorisable(Type& type, Rule& rule) const
{
	if (rule.Tokens.empty())
		return false;
	return rule.Tokens[0] == &type || rule.Tokens[rule.Tokens.size() - 1] == &type;
}
