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
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Rule.h"

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

std::string deamer::Rule::MakeConstructorArguments()
{
    std::string args;
	for(unsigned arg_count = 0; arg_count < Tokens.size(); arg_count++)
	{
        if (arg_count == 0)
            args += Tokens[arg_count]->MakeFunctionArgument();
        else
            args += ", " + Tokens[arg_count]->MakeFunctionArgument();
	}

    return args;
}

std::string deamer::Rule::MakeConstructorPrototype(Token* token_subject)
{
    return token_subject->TokenName + "(" + MakeConstructorArguments() + ")";
}

std::string deamer::Rule::MakeConstructors()
{
    std::string constructor_assignments;
    for (Token* token : Tokens)
        constructor_assignments += "    " + token->MakeConstructorTypeAssignment() + ";\n";

    return constructor_assignments;
}

std::string deamer::Rule::MakeConstructor(Token* token)
{
    return "{\n" + MakeConstructors() + "}\n";
}