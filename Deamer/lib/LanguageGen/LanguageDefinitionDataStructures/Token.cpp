/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
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