/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#ifndef DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONVECTORISEDRULEFORMATTER_H
#define DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONVECTORISEDRULEFORMATTER_H

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatter.h"

namespace deamer
{
	class BisonVectorisedRuleFormatter : public BisonRuleFormatter
	{
	private:
		std::string MakeExecutedCodeForProductionRule(Rule* rule) const override;
	public:
		BisonVectorisedRuleFormatter(std::string& languageName, unsigned currentLineNumber, bool isFirstType, Type& currentType);
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONVECTORISEDRULEFORMATTER_H