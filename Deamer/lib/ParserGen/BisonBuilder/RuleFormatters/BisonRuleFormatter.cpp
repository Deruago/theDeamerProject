/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
  */

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include <string>
#include <sstream>

deamer::BisonRuleFormatter::BisonRuleFormatter(std::string& languageName, unsigned currentLineNumber, bool isFirstType, Type* currentType, Rule* currentRule)
{
	LanguageName = languageName;
	CurrentLineNumber = currentLineNumber;
	CurrentType = currentType;
	CurrentRule = currentRule;
}

std::string deamer::BisonRuleFormatter::MakeRule() const
{
	return FormatRule();
}


std::string deamer::BisonRuleFormatter::FormatRule() const
{
	std::string newProductionRuleText = MakeIndentation() + MakeProductionRuleNotation() +
		MakeRuleProductionDefinition() + MakeBeginExecutedCodePartForProductionRule() + MakeExecutedCodeForProductionRule() + MakeEndExecutedCodePartForProductionRule() + EndProductionRule();
	return newProductionRuleText;
}

std::string deamer::BisonRuleFormatter::MakeRuleProductionDefinition() const
{
	std::string tmpString;
	for (int i = 0; i < CurrentRule->Tokens.size(); i++)
	{
		tmpString += CurrentRule->Tokens[i]->TokenName;
		if (i < CurrentRule->Tokens.size())
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
	return CurrentToken->TokenPermission.has_flag(TokenPermission_t::node);
}

bool deamer::BisonRuleFormatter::CurrentTokenHasAnAstNode(Token* CurrentToken) const
{
	return !CurrentToken->TokenPermission.has_flag(TokenPermission_t::ignore);
}

bool deamer::BisonRuleFormatter::CurrentTypeIsTheFirstType() const
{
	return CurrentType->TokenType.has_flag(TokenType_t::start);
}

std::string deamer::BisonRuleFormatter::MakeArgumentReferenceVariable(int& ArgumentCount) const
{
	return "$" + std::to_string(ArgumentCount + 1);
}

std::string deamer::BisonRuleFormatter::MakeArgument(const std::string& LanguageName, int& ArgumentCount, Token* CurrentToken) const
{
	std::string argument;
	//argument += "{";
	if (CurrentTokenIsNode(CurrentToken))
	{
		argument += MakeNewAstNode(LanguageName, ArgumentCount, CurrentToken);
	}
	else
	{
		argument += MakeArgumentReferenceVariable(ArgumentCount);
	}
	//argument += "}";
	return argument;
}

std::string deamer::BisonRuleFormatter::AddFirstArgument(const std::string& LanguageName, int& j) const
{
	std::string tmpString;
	j = 0;
	bool createdFirstParam = false;
	while (j < CurrentRule->Tokens.size() && !createdFirstParam)
	{
		Token* CurrentToken = CurrentRule->Tokens[j];
		j++;
		
		if (CurrentToken == CurrentType)
			continue;
		if (CurrentTokenHasAnAstNode(CurrentToken))
		{
			tmpString += MakeArgument(LanguageName, j, CurrentToken);
			createdFirstParam = true;
		}
	}

	return tmpString;
}

std::string deamer::BisonRuleFormatter::MakeNewAstNode(const std::string& LanguageName, int ArgumentCount, Token* CurrentToken) const
{
	return "new " + LanguageName + "::" + "AstNode_" + CurrentToken->TokenName + "($" + std::to_string(ArgumentCount + 1) + ")";
}

std::string deamer::BisonRuleFormatter::AddRestOfAllArguments(const std::string& LanguageName, int ArgumentCount) const
{
	std::string tmpString;
	int tokenCount = 0;
	for (;ArgumentCount < CurrentRule->Tokens.size(); ArgumentCount++)
	{
		Token* CurrentToken = CurrentRule->Tokens[ArgumentCount];
		if (CurrentToken == CurrentType)
			continue;
		if (!CurrentTokenHasAnAstNode(CurrentToken))
		{
			continue;
		}

		if (tokenCount > 0)
		{
			tmpString += ", ";
		}
		
		tmpString += MakeArgument(LanguageName, ArgumentCount, CurrentToken);
		tokenCount++;
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

std::string deamer::BisonRuleFormatter::AddArgumentsToAstType(const std::string& LanguageName) const
{
	int argumentCount = 0;
	return "(" + AddRestOfAllArguments(LanguageName, argumentCount) + ")" + MakeEndAddToMainTypeLine() + ";\n";
}

std::string deamer::BisonRuleFormatter::MakeAstTree(const std::string& LanguageName) const
{
	return  "      " + LanguageName + "::" + "AstTree_" + CurrentType->TokenName + "* ASTTREE_" + CurrentType->TokenName + " = new " + LanguageName + "::" + "AstTree_" + CurrentType->TokenName;
}

std::string deamer::BisonRuleFormatter::MakeAddToMainTypeLine() const
{
	if (CurrentType->TokenType.has_flag(TokenType_t::vector))
		return MakeVectorCreationLogic() + "      $$->push_back(new ";
	else
		return "      $$ = new ";
}

std::string deamer::BisonRuleFormatter::MakeVectorCreationLogic() const
{
	std::string vectorised_check_allocation;
	if (CurrentRule->RuleType.has_flag(RuleType_t::recursive))
	{
		vectorised_check_allocation += "      $$ = $" + std::to_string(GetRecursiveTypeLocationInRule()) + ";\n";
	}
	else
	{
		vectorised_check_allocation += "      $$ = new std::vector<" + TypeToClassName(CurrentType) + "*>();\n";
	}
	return vectorised_check_allocation;
}

unsigned deamer::BisonRuleFormatter::GetRecursiveTypeLocationInRule() const
{
	unsigned argument_place_in_rule = 1;
	for (Token* token : CurrentRule->Tokens)
	{
		if (token == CurrentType)
			return argument_place_in_rule;
		argument_place_in_rule++;
	}
	return argument_place_in_rule;
}

std::string deamer::BisonRuleFormatter::TypeToClassName(Type* type) const
{
	return LanguageName + "::AstNode_" + type->TokenName;
}

std::string deamer::BisonRuleFormatter::MakeEndAddToMainTypeLine() const
{
	if (CurrentType->TokenType.has_flag(TokenType_t::vector))
		return ")";
	else
		return "";
}

std::string deamer::BisonRuleFormatter::MakeAstNode(const std::string& LanguageName) const
{
	return MakeAddToMainTypeLine() + LanguageName + "::" + "AstNode_" + CurrentType->TokenName;
}

std::string deamer::BisonRuleFormatter::MakeAstNode(const std::string& LanguageName, const std::string& TokenName) const
{
	return MakeAddToMainTypeLine() + LanguageName + "::" + "AstNode_" + TokenName;
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
	return "      ASTTREE_" + CurrentType->TokenName + "->SetCurrentTree(ASTTREE_" + CurrentType->TokenName + ");\n";
}