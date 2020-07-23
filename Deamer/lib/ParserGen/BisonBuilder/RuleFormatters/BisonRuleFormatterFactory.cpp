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
	RuleType_t ruleType, std::string& languageName, unsigned currentLineNumber, bool isFirstType,
	Type& currentType) const
{
	switch(ruleType)
	{
	case RuleType_t::empty:
		return std::make_unique<BisonEmptyRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType);
	case RuleType_t::standard:
		return std::make_unique<BisonStandardRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType);
	case RuleType_t::grouped:
		return std::make_unique<BisonGroupedRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType);
	case RuleType_t::vectorised:
		return std::make_unique<BisonVectorisedRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType);
	}
	return std::make_unique<BisonStandardRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType);
}
