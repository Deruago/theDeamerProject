/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 * -October 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonGroupedRuleFormatter.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/TypeAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"

deamer::BisonGroupedRuleFormatter::BisonGroupedRuleFormatter(std::string& languageName, unsigned currentLineNumber,
                                                             bool isFirstType, Type* currentType, Rule* currentRule) : BisonRuleFormatter(languageName, currentLineNumber, isFirstType, currentType, currentRule)
{
	const unsigned types = TypeAnalyzer(*currentType).GetTokenTypesOccuringInType(*currentType, groupNonTerminalTypes, groupTerminalTypes);
	if (types == 1)
		isPureGroup = true;
	else
		isPureGroup = false;
}

std::string deamer::BisonGroupedRuleFormatter::MakeExecutedCodeForProductionRule() const
{
	Token* currentToken = CurrentRule->Tokens[0];
	if (isPureGroup)
	{
		return MakeExecutedCodeForPureGroup(*currentToken);
	}
	else
	{
		return MakeExecutedCodeForMixedGroup(*currentToken);	
	}
}

std::string deamer::BisonGroupedRuleFormatter::MakeExecutedCodeForPureGroup(const Token& currentToken) const
{
	switch(groupNonTerminalTypes.enum_value())
	{
	case TokenType_t::start:
	case TokenType_t::standard:
		return MakeExecutedCodeForPureGroupStandard(currentToken);
	case TokenType_t::vector:
		return MakeExecutedCodeForPureGroupVector(currentToken);

	case TokenType_t::none:
	case TokenType_t::grouped:
	case TokenType_t::all:
		break;
	}
	switch(groupTerminalTypes.enum_value())
	{
	case TokenPermission_t::node:
		return MakeExecutedCodeForPureGroupNode(currentToken);
	case TokenPermission_t::ignore:
		return MakeExecutedCodeForPureGroupIgnore(currentToken);
	case TokenPermission_t::delete_:
		return MakeExecutedCodeForPureGroupDelete(currentToken);
		
	case TokenPermission_t::none:
	case TokenPermission_t::all:
		break;
	}
	return "";
}

std::string deamer::BisonGroupedRuleFormatter::MakeExecutedCodeForMixedGroup(const Token& currentToken) const
{
	if (currentToken.TokenPermission.has_flag(TokenPermission_t::node))
		return MakeAstNode(LanguageName, currentToken.TokenName) + "($1)" + MakeEndAddToMainTypeLine() + ";\n";
	else
		return "      $$ = $1\n";
}

std::string deamer::BisonGroupedRuleFormatter::MakeExecutedCodeForPureGroupStandard(const Token& currentToken) const
{
	return MakeNonTerminalCode(currentToken);
}

std::string deamer::BisonGroupedRuleFormatter::MakeExecutedCodeForPureGroupVector(const Token& currentToken) const
{
	return MakeVectorCode(currentToken);
}

std::string deamer::BisonGroupedRuleFormatter::MakeExecutedCodeForPureGroupNode(const Token& currentToken) const
{
	return MakeTerminalCode(currentToken);
}

std::string deamer::BisonGroupedRuleFormatter::MakeExecutedCodeForPureGroupIgnore(const Token& currentToken) const
{
	return MakeIgnoreCodeWithoutGroupObject(currentToken);
}

std::string deamer::BisonGroupedRuleFormatter::MakeExecutedCodeForPureGroupDelete(const Token& currentToken) const
{
	return MakeIgnoreCodeWithoutGroupObject(currentToken);
}

std::string deamer::BisonGroupedRuleFormatter::MakeNonTerminalCode(const Token& currentToken) const
{
	return "      $$ = $1\n";
}

std::string deamer::BisonGroupedRuleFormatter::MakeVectorCode(const Token& currentToken) const
{
	return "";
}

std::string deamer::BisonGroupedRuleFormatter::MakeTerminalCode(const Token& currentToken) const
{
	return MakeAstNode(LanguageName, currentToken.TokenName) + "($1)" + MakeEndAddToMainTypeLine() + ";\n";
}

std::string deamer::BisonGroupedRuleFormatter::MakeIgnoreCodeWithoutGroupObject(const Token& currentToken) const
{
	return "";
}

std::string deamer::BisonGroupedRuleFormatter::MakeIgnoreCodeWithGroupObject(const Token& currentToken) const
{
	return "";
}