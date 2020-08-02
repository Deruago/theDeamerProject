/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonStandardRuleFormatter.h"

deamer::BisonStandardRuleFormatter::BisonStandardRuleFormatter(std::string& languageName, unsigned currentLineNumber,
                                                               bool isFirstType, Type* currentType, Rule* currentRule) : BisonRuleFormatter(languageName, currentLineNumber, isFirstType, currentType, currentRule)
{
}


std::string deamer::BisonStandardRuleFormatter::MakeExecutedCodeForProductionRule() const
{
	return FormatTypeRulePart();
}

std::string deamer::BisonStandardRuleFormatter::FormatTypeRulePart() const
{
	return MakeRuleExecutionPart() + MakeOutputCodeWhenNodeIsStartType();
}

std::string deamer::BisonStandardRuleFormatter::MakeRuleExecutionPart() const
{
	return MakeAstType(LanguageName) + AddArgumentsToAstType(LanguageName);
}