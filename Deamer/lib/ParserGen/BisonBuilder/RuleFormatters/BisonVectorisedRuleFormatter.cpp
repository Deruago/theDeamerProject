/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonVectorisedRuleFormatter.h"

std::string deamer::BisonVectorisedRuleFormatter::MakeExecutedCodeForProductionRule() const
{
	std::string vectorised_rule;
	AddRuleToVectorType(vectorised_rule);
	return vectorised_rule;
}

void deamer::BisonVectorisedRuleFormatter::AddRuleToVectorType(std::string& vectorised_rule) const
{
	vectorised_rule += MakeAstType(LanguageName) + AddArgumentsToAstType(LanguageName);
}

std::string deamer::BisonVectorisedRuleFormatter::MakeAstTypeFromTypeVector(Type* type) const
{
	return "new " + TypeToClassName(type);
}

deamer::BisonVectorisedRuleFormatter::BisonVectorisedRuleFormatter(std::string& languageName,
                                                                   unsigned currentLineNumber, bool isFirstType, Type* currentType, Rule* currentRule) : BisonRuleFormatter(languageName, currentLineNumber, isFirstType, currentType, currentRule)
{
}
