/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#include "Deamer/LanguageGen/Token.h"
#include <string>
#include <iostream>

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

void deamer::Token::SetBaseGroupTokensIsVector(const bool cond)
{
    for (Token* token : BaseGroupTokens)
    {
        token->SetBaseGroupTokensIsVector(cond);
        token->IsVector = cond;
    }
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
