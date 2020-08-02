/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonEmptyRuleFormatter.h"

deamer::BisonEmptyRuleFormatter::BisonEmptyRuleFormatter(std::string& languageName, unsigned currentLineNumber,
                                                         bool isFirstType, Type* currentType, Rule* currentRule) : BisonRuleFormatter(languageName, currentLineNumber, isFirstType, currentType, currentRule)
{
}

std::string deamer::BisonEmptyRuleFormatter::MakeExecutedCodeForProductionRule() const
{
	if (CurrentType->TokenType.has_flag(TokenType_t::vector))
		return "          $$ = new std::vector<" + TypeToClassName(CurrentType) + "*>();\n";
	else
		return "";
}