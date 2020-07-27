/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonGroupedRuleFormatter.h"

std::string deamer::BisonGroupedRuleFormatter::MakeExecutedCodeForProductionRule(Rule* rule) const
{
	Token* currentToken = rule->Tokens[0];
	if (currentToken->IsNode)
		return MakeAstNode(LanguageName, currentToken->TokenName) + "($1);";
	else
		return "      $$ = $1";
}

deamer::BisonGroupedRuleFormatter::BisonGroupedRuleFormatter(std::string& languageName, unsigned currentLineNumber,
                                                             bool isFirstType, Type& currentType) : BisonRuleFormatter(languageName, currentLineNumber, isFirstType, currentType)
{
}
