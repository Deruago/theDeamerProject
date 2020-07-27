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

std::string deamer::Token::MakeFunctionArgument()
{
    if (IsVector)
        return "std::vector<AstNode_" + TokenName + ">* " + TokenName + "_vector";
    else
        return "AstNode_" + TokenName + "* " + TokenName;
}

std::string deamer::Token::MakeTypeCallAsClassField()
{
    if (IsVector)
        return "_" + TokenName + "_vector";
    else
        return "_" + TokenName;
}

std::string deamer::Token::MakeTypeAsCtorInputVariable()
{
    if (IsVector)
        return TokenName + "_vector";
    else
        return TokenName;
}

std::string deamer::Token::MakeConstructorTypeAssignment()
{
    return MakeTypeCallAsClassField() + " = " + MakeTypeAsCtorInputVariable();
}

std::string deamer::Token::MakeTypeAsClassField()
{
    if (IsVector)
        return "std::vector<AstNode_" + TokenName + "*> " + MakeTypeCallAsClassField();
    else
        return "AstNode_" + TokenName + "* " + MakeTypeCallAsClassField();
}
