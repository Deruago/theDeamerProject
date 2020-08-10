/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEFORMATTER_RULEFORMATTER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEFORMATTER_RULEFORMATTER_H
#include <string>

#include "Deamer/ParserGen/BisonBuilder/BisonRuleSectionFormatter.h"

namespace deamer
{
	class Token;

	class RuleFormatter
	{
	private:
	protected:
	public:
		RuleFormatter() = default;
		~RuleFormatter() = default;

		std::string MakeConstructorArguments(Token* token_subject, Rule& rule);
		std::string MakeConstructorPrototype(Token* token_subject, Rule& rule);
		std::string MakeConstructors(Token* token_subject, Rule& rule);
		std::string MakeConstructor(Token* token, Rule& rule);
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEFORMATTER_RULEFORMATTER_H