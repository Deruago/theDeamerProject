/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/LanguageAnalyzer/LanguageFormatter/RuleFormatter.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"

std::string deamer::RuleFormatter::MakeConstructorArguments(Token* token_subject, Rule& rule)
{
	std::string args;
	unsigned arg_count_implemented = 0;
	for (auto& Token : rule.Tokens)
	{
		if (Token->TokenPermission.has_flag(TokenPermission_t::ignore))
			continue;
		if (Token == token_subject)
			continue;
		if (arg_count_implemented == 0)
		{
			args += Token->MakeFunctionArgument();
			arg_count_implemented++;
		}
		else
		{
			args += ", " + Token->MakeFunctionArgument();
			arg_count_implemented++;
		}
	}

	return args;
}

std::string deamer::RuleFormatter::MakeConstructorPrototype(Token* token_subject, Rule& rule)
{
	return token_subject->TokenName + "(" + MakeConstructorArguments(token_subject, rule) + ")";
}

std::string deamer::RuleFormatter::MakeConstructors(Token* token_subject, Rule& rule)
{
	std::string constructor_assignments;
	for (Token* token : rule.Tokens)
		if (!token->TokenPermission.has_flag(TokenPermission_t::ignore) && token != token_subject)
		{
			constructor_assignments += "    " + token->MakeConstructorTypeAssignment() + ";\n";
			if (token->TokenType.has_flag(TokenType_t::vector))
			{
				constructor_assignments += "    for(AstNode_" + token->TokenName + "* _" + token->MakeTypeCallAsClassField() + " : *" + token->MakeTypeAsCtorInputVariable() + ")\n";
				constructor_assignments += "        AstNodes.push_back(_" + token->MakeTypeCallAsClassField() + ");\n";
			}
			else
			{
				constructor_assignments += "    AstNodes.push_back(" + token->MakeTypeAsCtorInputVariable() + ");\n";
			}
		}

	return constructor_assignments;
}

std::string deamer::RuleFormatter::MakeConstructor(Token* token, Rule& rule)
{
	return "{\n" + MakeConstructors(token, rule) + "}\n";
}