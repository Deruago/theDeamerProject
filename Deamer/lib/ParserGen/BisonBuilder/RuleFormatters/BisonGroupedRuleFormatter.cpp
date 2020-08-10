/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonGroupedRuleFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"

std::string deamer::BisonGroupedRuleFormatter::MakeExecutedCodeForProductionRule() const
{
	Token* currentToken = CurrentRule->Tokens[0];
	if (currentToken->TokenPermission.has_flag(TokenPermission_t::node))
		return MakeAstNode(LanguageName, currentToken->TokenName) + "($1)" + MakeEndAddToMainTypeLine() + ";\n";
	else
		return "      $$ = $1\n";
}

deamer::BisonGroupedRuleFormatter::BisonGroupedRuleFormatter(std::string& languageName, unsigned currentLineNumber,
                                                             bool isFirstType, Type* currentType, Rule* currentRule) : BisonRuleFormatter(languageName, currentLineNumber, isFirstType, currentType, currentRule)
{
}
