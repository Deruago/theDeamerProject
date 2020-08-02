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
#include <string>
#include <iostream>

//deamer::Token::Token(const std::string& tokenName, const bool isNode, const bool createAst)
//{
//    TokenName = tokenName;
//    IsNode = isNode;
//    CreateAst = createAst;
//}

deamer::Token::Token(const std::string& tokenName, const BitwiseEnum<TokenType_t> tokenType,
	const BitwiseEnum<TokenPermission_t> tokenPermission)
{
    TokenName = tokenName;
    TokenType = tokenType;
    TokenPermission = tokenPermission;
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
    for (Type* type : BaseGroupTokens)
    {
        if (type->TokenType != TokenType_t::start)
        {
            type->SetBaseGroupTokensIsVector(cond);
            type->TokenType.set_flag(TokenType_t::vector, cond);
        }
    }
}

std::string deamer::Token::MakeFunctionArgument()
{
    if (TokenType.has_flag(TokenType_t::vector))
        return "std::vector<AstNode_" + TokenName + "*>* " + TokenName + "_vector";
    else
        return "AstNode_" + TokenName + "* " + TokenName;
}

std::string deamer::Token::MakeTypeCallAsClassField()
{
    if (TokenType.has_flag(TokenType_t::vector))
        return "_" + TokenName + "_vector";
    else
        return "_" + TokenName;
}

std::string deamer::Token::MakeTypeAsCtorInputVariable()
{
    if (TokenType.has_flag(TokenType_t::vector))
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
    if (TokenType.has_flag(TokenType_t::vector))
        return "std::vector<AstNode_" + TokenName + "*>* " + MakeTypeCallAsClassField();
    else
        return "AstNode_" + TokenName + "* " + MakeTypeCallAsClassField();
}
