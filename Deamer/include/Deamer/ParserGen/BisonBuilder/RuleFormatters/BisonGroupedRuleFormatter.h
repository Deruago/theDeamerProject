/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#ifndef DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONGROUPEDRULEFORMATTER_H
#define DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONGROUPEDRULEFORMATTER_H

#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatter.h"
#include "Deamer/Types/BitwiseEnum.h"

namespace deamer
{
	class BisonGroupedRuleFormatter : public BisonRuleFormatter
	{
	private:
		std::string MakeExecutedCodeForMixedGroup(const Token& currentToken) const;
		
		std::string MakeExecutedCodeForPureGroup(const Token& currentToken) const;
		std::string MakeExecutedCodeForPureGroupStandard(const Token& currentToken) const;
		std::string MakeExecutedCodeForPureGroupVector(const Token& currentToken) const;
		std::string MakeExecutedCodeForPureGroupNode(const Token& currentToken) const;
		std::string MakeExecutedCodeForPureGroupIgnore(const Token& currentToken) const;
		std::string MakeExecutedCodeForPureGroupDelete(const Token& currentToken) const;
		
		std::string MakeNonTerminalCode(const Token& currentToken) const;
		std::string MakeVectorCode(const Token& currentToken) const;
		std::string MakeTerminalCode(const Token& currentToken) const;
		std::string MakeIgnoreCodeWithoutGroupObject(const Token& currentToken) const;
		std::string MakeIgnoreCodeWithGroupObject(const Token& currentToken) const;

		std::string MakeExecutedCodeForProductionRule() const override;
		bool isPureGroup = false; //Does it exists of 1 group?
		BitwiseEnum<TokenType_t> groupNonTerminalTypes;    //The types occuring in our group
		BitwiseEnum<TokenPermission_t> groupTerminalTypes; //The types occuring in our group
	public:
		BisonGroupedRuleFormatter(std::string& languageName, unsigned currentLineNumber, bool isFirstType, Type* currentType, Rule* currentRule);
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONGROUPEDRULEFORMATTER_H