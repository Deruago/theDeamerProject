/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#ifndef DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONRULEFORMATTER_H
#define DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONRULEFORMATTER_H

#include "Deamer/ParserGen/BisonBuilder/BisonRuleSectionFormatter.h"
#include "Deamer/LanguageGen/Type.h"
#include <string>

namespace deamer
{
	class Token;
	class Rule;

	class BisonRuleFormatter
	{
	private:
		std::string MakeRuleProductionDefinition(Rule* rule) const;
		virtual std::string MakeExecutedCodeForProductionRule(Rule* rule) const = 0;

		std::string MakeBeginExecutedCodePartForProductionRule() const;
		std::string MakeEndExecutedCodePartForProductionRule() const;
	protected:
		std::string LanguageName = "";
		unsigned CurrentLineNumber;
		bool IsFirstType;
		Type CurrentType = Type("", false, false);
		bool CurrentTokenIsNode(Token* CurrentToken) const;
		bool CurrentTokenHasAnAstNode(Token* CurrentToken) const;
		bool CurrentTypeIsTheFirstType() const;
		std::string MakeArgumentReferenceVariable(int& ArgumentCount) const;
		std::string MakeArgument(const std::string& LanguageName, int& ArgumentCount, Token* CurrentToken) const;
		std::string AddFirstArgument(const std::string& LanguageName, Rule* rule, int& j) const;
		std::string MakeNewAstNode(const std::string& LanguageName, int ArgumentCount,
		                           Token* CurrentToken) const;
		std::string AddRestOfAllArguments(const std::string& LanguageName, Rule* rule, int ArgumentCount) const;
		std::string MakeAstType(const std::string& LanguageName) const;
		std::string AddArgumentsToAstType(const std::string& LanguageName, Rule* rule) const;
		std::string MakeAstTree(const std::string& LanguageName) const;
		std::string MakeAstNode(const std::string& LanguageName) const;
		std::string MakeAstNode(const std::string& LanguageName, const std::string& TokenName) const;
		std::string MakeOutputCodeForAstTree() const;
		std::string MakeOutputCodeWhenNodeIsStartType() const;
		std::string MakeProductionRuleNotation() const;
		std::string FormatRule(Rule* rule) const;
	public:
		BisonRuleFormatter(std::string& languageName, unsigned currentLineNumber, bool isFirstType, Type& currentType);
		virtual ~BisonRuleFormatter() = default;
		std::string MakeRule(Rule* rule) const;
		const char EndProductionRule() const;
		const char* MakeIndentation() const;
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONRULEFORMATTER_H