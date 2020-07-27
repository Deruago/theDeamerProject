/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Type.h"
#include <iostream>
#include <string>

deamer::Type::Type(const std::string& typeName, const bool createAst, const bool groupedType) : Token(typeName, false, createAst)
{
    GroupedType = groupedType;
}


void deamer::Type::AddRule(Rule* newRule)
{
    Rules.push_back(newRule);
}

void deamer::Type::PrintType()
{
    PrintToken();
    PrintRules();
}

void deamer::Type::PrintRules()
{
    for(auto i = 0; i < Rules.size(); i++)
    {
        Rules[i]->PrintRule();
    }
}

std::vector<deamer::Token*> deamer::Type::GetVectorOfUniqueTokensDefiningThisType()
{
    std::vector<Token*> token_vector;
    for (Rule* rule : Rules)
        for (Token* token : rule->Tokens)
            AddTokenToVectorIfNotAlreadyInVector(token_vector, token);
    return token_vector;
}

void deamer::Type::AddTokenToVectorIfNotAlreadyInVector(std::vector<Token*>& tokens, Token* token)
{
    for (Token* token_in_vector : tokens)
        if (token_in_vector == token)
            return;
    tokens.push_back(token);
}