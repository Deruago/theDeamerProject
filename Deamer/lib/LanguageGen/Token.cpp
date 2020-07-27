/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#include <iostream>
#include <string>
#include "Deamer/LanguageGen/Token.h"

deamer::Token::Token(const std::string& tokenName, const bool isNode, const bool createAst)
{
    TokenName = tokenName;
    IsNode = isNode;
    CreateAst = createAst;
}

void deamer::Token::PrintToken()
{
    std::cout << TokenName << ' ';
}

void deamer::Token::AddBaseToken(Token* token)
{
    BaseTokens.push_back(token);
}

void deamer::Token::AddReferenceToTokenThatUsesThisToken()
{
    TotalAmountOfTypesThatUsesThisToken++;
}

void deamer::Token::RemoveReferenceThatUsedThisToken()
{
    --TotalAmountOfTypesThatUsesThisToken;
}
