/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#ifndef DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONGROUPEDRULEFORMATTER_H
#define DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONGROUPEDRULEFORMATTER_H

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatter.h"

namespace deamer
{
	class BisonGroupedRuleFormatter : public BisonRuleFormatter
	{
	private:
		std::string MakeExecutedCodeForProductionRule() const override;
	public:
		BisonGroupedRuleFormatter(std::string& languageName, unsigned currentLineNumber, bool isFirstType, Type* currentType, Rule* currentRule);
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONGROUPEDRULEFORMATTER_H