/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#ifndef DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONRULEFORMATTERFACTORY_H
#define DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONRULEFORMATTERFACTORY_H

#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Node.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include <memory>
#include <string>

namespace deamer
{
	class BisonRuleFormatter;
	
	class BisonRuleFormatterFactory
	{
	public:
		BisonRuleFormatterFactory() = default;
		~BisonRuleFormatterFactory() = default;
		std::unique_ptr<deamer::BisonRuleFormatter> MakeRuleFormatter(Rule* rule,
		                                                              std::string& languageName, unsigned currentLineNumber,
		                                                              bool isFirstType, Type* currentType) const;
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONRULEFORMATTERFACTORY_H