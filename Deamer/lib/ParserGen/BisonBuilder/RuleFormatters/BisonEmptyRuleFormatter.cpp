/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonEmptyRuleFormatter.h"

deamer::BisonEmptyRuleFormatter::BisonEmptyRuleFormatter(std::string& languageName, unsigned currentLineNumber,
                                                         bool isFirstType, Type& currentType) : BisonRuleFormatter(languageName, currentLineNumber, isFirstType, currentType)
{
}

std::string deamer::BisonEmptyRuleFormatter::MakeExecutedCodeForProductionRule(Rule* rule) const
{
	return "";
}