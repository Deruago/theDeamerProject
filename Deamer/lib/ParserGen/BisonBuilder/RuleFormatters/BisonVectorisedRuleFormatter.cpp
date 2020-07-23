/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonVectorisedRuleFormatter.h"

std::string deamer::BisonVectorisedRuleFormatter::MakeExecutedCodeForProductionRule(Rule* rule) const
{
	return "";
}

deamer::BisonVectorisedRuleFormatter::BisonVectorisedRuleFormatter(std::string& languageName,
                                                                   unsigned currentLineNumber, bool isFirstType, Type& currentType) : BisonRuleFormatter(languageName, currentLineNumber, isFirstType, currentType)
{
}
