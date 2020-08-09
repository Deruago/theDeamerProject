/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include <iostream>
#include <string>
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"

deamer::Rule::Rule(const std::vector<Token*>& tokens)
{
    Tokens = tokens;
}

void deamer::Rule::PrintRule()
{
    for (auto& Token : Tokens)
    {
	    Token->PrintToken();
    }
    std::cout << "\n";
}

bool deamer::Rule::IsEmpty() const
{
    return Tokens.empty();
}

std::string deamer::Rule::MakeConstructorArguments(Token* token_subject)
{
    std::string args;
    unsigned arg_count_implemented = 0;
	for(unsigned arg_count = 0; arg_count < Tokens.size(); arg_count++)
	{
	    if (Tokens[arg_count]->TokenPermission.has_flag(TokenPermission_t::ignore))
 	       continue;
	    if (Tokens[arg_count] == token_subject)
  	      continue;
	    if (arg_count_implemented == 0)
	    {
 	       args += Tokens[arg_count]->MakeFunctionArgument();
 	       arg_count_implemented++;
	    }
	    else
	    {
	        args += ", " + Tokens[arg_count]->MakeFunctionArgument();
	        arg_count_implemented++;
	    }
	}

    return args;
}

std::string deamer::Rule::MakeConstructorPrototype(Token* token_subject)
{
    return token_subject->TokenName + "(" + MakeConstructorArguments(token_subject) + ")";
}

std::string deamer::Rule::MakeConstructors(Token* token_subject)
{
    std::string constructor_assignments;
    for (Token* token : Tokens)
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

std::string deamer::Rule::MakeConstructor(Token* token)
{
    return "{\n" + MakeConstructors(token) + "}\n";
}
