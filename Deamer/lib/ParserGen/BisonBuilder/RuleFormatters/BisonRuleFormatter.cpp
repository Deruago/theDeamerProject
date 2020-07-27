/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatter.h"
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Type.h"
#include "Deamer/LanguageGen/Rule.h"
#include <string>
#include <sstream>

deamer::BisonRuleFormatter::BisonRuleFormatter(std::string& languageName, unsigned currentLineNumber, bool isFirstType, Type& currentType)
{
	LanguageName = languageName;
	CurrentLineNumber = currentLineNumber;
	IsFirstType = isFirstType;
	CurrentType = currentType;
}

std::string deamer::BisonRuleFormatter::MakeRule(Rule* rule) const
{
	return FormatRule(rule);
}


std::string deamer::BisonRuleFormatter::FormatRule(Rule* rule) const
{
	std::string newProductionRuleText = MakeIndentation() + MakeProductionRuleNotation() +
		MakeRuleProductionDefinition(rule) + MakeBeginExecutedCodePartForProductionRule() + MakeExecutedCodeForProductionRule(rule) + MakeEndExecutedCodePartForProductionRule() + EndProductionRule();
	return newProductionRuleText;
}

std::string deamer::BisonRuleFormatter::MakeRuleProductionDefinition(Rule* rule) const
{
	std::string tmpString;
	for (int i = 0; i < rule->Tokens.size(); i++)
	{
		tmpString += rule->Tokens[i]->TokenName;
		if (i < rule->Tokens.size())
		{
			tmpString += ' ';
		}
	}
	return tmpString;
}

const char* deamer::BisonRuleFormatter::MakeIndentation() const
{
	return "    ";
}

std::string deamer::BisonRuleFormatter::MakeProductionRuleNotation() const
{
	if (CurrentLineNumber >= 1)
		return "| ";
	else
		return "  ";
}

std::string deamer::BisonRuleFormatter::MakeBeginExecutedCodePartForProductionRule() const
{
	return "{\n";
}

std::string deamer::BisonRuleFormatter::MakeEndExecutedCodePartForProductionRule() const
{
	return "    }";
}

const char deamer::BisonRuleFormatter::EndProductionRule() const
{
	return '\n';
}

bool deamer::BisonRuleFormatter::CurrentTokenIsNode(Token* CurrentToken) const
{
	return CurrentToken->IsNode;
}

bool deamer::BisonRuleFormatter::CurrentTokenHasAnAstNode(Token* CurrentToken) const
{
	return CurrentToken->CreateAst;
}

bool deamer::BisonRuleFormatter::CurrentTypeIsTheFirstType() const
{
	return IsFirstType;
}

std::string deamer::BisonRuleFormatter::MakeArgumentReferenceVariable(int& ArgumentCount) const
{
	return "$" + std::to_string(ArgumentCount + 1);
}

std::string deamer::BisonRuleFormatter::MakeArgument(const std::string& LanguageName, int& ArgumentCount, Token* CurrentToken) const
{
	if (CurrentTokenIsNode(CurrentToken))
	{
		return MakeNewAstNode(LanguageName, ArgumentCount, CurrentToken);
	}
	else
	{
		return MakeArgumentReferenceVariable(ArgumentCount);
	}
}

std::string deamer::BisonRuleFormatter::AddFirstArgument(const std::string& LanguageName, Rule* rule, int& j) const
{
	std::string tmpString;
	j = 0;
	bool createdFirstParam = false;
	while (j < rule->Tokens.size() && !createdFirstParam)
	{
		Token* CurrentToken = rule->Tokens[j];
		if (CurrentTokenHasAnAstNode(CurrentToken))
		{
			tmpString += MakeArgument(LanguageName, j, CurrentToken);
			createdFirstParam = true;
		}
		j++;
	}

	return tmpString;
}

std::string deamer::BisonRuleFormatter::MakeNewAstNode(const std::string& LanguageName, int ArgumentCount, Token* CurrentToken) const
{
	return "new " + LanguageName + "::" + "AstNode_" + CurrentToken->TokenName + "($" + std::to_string(ArgumentCount + 1) + ")";
}

std::string deamer::BisonRuleFormatter::AddRestOfAllArguments(const std::string& LanguageName, Rule* rule, int ArgumentCount) const
{
	std::string tmpString;
	for (;ArgumentCount < rule->Tokens.size(); ArgumentCount++)
	{
		Token* CurrentToken = rule->Tokens[ArgumentCount];
		if (!CurrentTokenHasAnAstNode(CurrentToken))
		{
			continue;
		}

		tmpString += ", " + MakeArgument(LanguageName, ArgumentCount, CurrentToken);
	}

	return tmpString;
}

std::string deamer::BisonRuleFormatter::MakeAstType(const std::string& LanguageName) const
{
	if (CurrentTypeIsTheFirstType())
	{
		return MakeAstTree(LanguageName);
	}
	else
	{
		return MakeAstNode(LanguageName);
	}
}

std::string deamer::BisonRuleFormatter::AddArgumentsToAstType(const std::string& LanguageName, Rule* rule) const
{
	int argumentCount;
	return "({" +AddFirstArgument(LanguageName, rule, argumentCount) + AddRestOfAllArguments(LanguageName, rule, argumentCount) + "});\n";
}


std::string deamer::BisonRuleFormatter::MakeAstTree(const std::string& LanguageName) const
{
	return  "      " + LanguageName + "::" + "AstTree_" + CurrentType.TokenName + "* ASTTREE_" + CurrentType.TokenName + " = new " + LanguageName + "::" + "AstTree_" + CurrentType.TokenName;
}

std::string deamer::BisonRuleFormatter::MakeAstNode(const std::string& LanguageName) const
{
	return + "      $$ = new " + LanguageName + "::" + "AstNode_" + CurrentType.TokenName;
}

std::string deamer::BisonRuleFormatter::MakeAstNode(const std::string& LanguageName, const std::string& TokenName) const
{
	return +"      $$ = new " + LanguageName + "::" + "AstNode_" + TokenName;
}

std::string deamer::BisonRuleFormatter::MakeOutputCodeWhenNodeIsStartType() const
{
	if (CurrentTypeIsTheFirstType())
	{
		return MakeOutputCodeForAstTree();
	}
	return "";
}

std::string deamer::BisonRuleFormatter::MakeOutputCodeForAstTree() const
{
	return "      ASTTREE_" + CurrentType.TokenName + "->SetCurrentTree(ASTTREE_" + CurrentType.TokenName + ");\n";
}