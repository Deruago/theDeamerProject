/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#ifndef DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONSTANDARDRULEFORMATTER_H
#define DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONSTANDARDRULEFORMATTER_H

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatter.h"

namespace deamer
{
	class BisonStandardRuleFormatter : public BisonRuleFormatter
	{
	private:
		std::string MakeExecutedCodeForProductionRule(Rule* rule) const override;
		std::string FormatTypeRulePart(Rule* rule) const;
		std::string MakeRuleExecutionPart(Rule* rule) const;
	public:
		BisonStandardRuleFormatter(std::string& languageName, unsigned currentLineNumber, bool isFirstType, Type& currentType);
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONSTANDARDRULEFORMATTER_H