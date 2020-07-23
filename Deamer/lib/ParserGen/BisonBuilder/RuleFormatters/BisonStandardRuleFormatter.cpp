/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonStandardRuleFormatter.h"

deamer::BisonStandardRuleFormatter::BisonStandardRuleFormatter(std::string& languageName, unsigned currentLineNumber,
                                                               bool isFirstType, Type& currentType) : BisonRuleFormatter(languageName, currentLineNumber, isFirstType, currentType)
{
}


std::string deamer::BisonStandardRuleFormatter::MakeExecutedCodeForProductionRule(Rule* rule) const
{
	return FormatTypeRulePart(rule);
}

std::string deamer::BisonStandardRuleFormatter::FormatTypeRulePart(Rule* rule) const
{
	return "{\n" + MakeRuleExecutionPart(rule) + MakeOutputCodeWhenNodeIsStartType() + "    }";
}

std::string deamer::BisonStandardRuleFormatter::MakeRuleExecutionPart(Rule* rule) const
{
	return MakeAstType(LanguageName) + AddArgumentsToAstType(LanguageName, rule);
}