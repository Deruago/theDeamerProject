/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatterFactory.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatter.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonEmptyRuleFormatter.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonGroupedRuleFormatter.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonVectorisedRuleFormatter.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonStandardRuleFormatter.h"
#include <memory>

std::unique_ptr<deamer::BisonRuleFormatter> deamer::BisonRuleFormatterFactory::MakeRuleFormatter(
	Rule* rule, std::string& languageName, unsigned currentLineNumber, bool isFirstType,
	Type* currentType) const
{
	BitwiseEnum<RuleType_t> ruleType = rule->RuleType;
	if(ruleType.has_flag(RuleType_t::empty))
	{
		return std::make_unique<BisonEmptyRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType, rule);
	}
	if(ruleType.has_flag(RuleType_t::standard))
	{
		return std::make_unique<BisonStandardRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType, rule);
	}
	if (ruleType.has_flag(RuleType_t::grouped))
	{
		return std::make_unique<BisonGroupedRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType, rule);
	}
	if (ruleType.has_flag(RuleType_t::vectorised))
	{
		return std::make_unique<BisonVectorisedRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType, rule);
	}
	return std::make_unique<BisonStandardRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType, rule);
}
