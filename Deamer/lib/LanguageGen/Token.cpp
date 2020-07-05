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

deamer::Token::Token(const std::string tokenName, const bool isNode, const bool createAst)
{
    deamer::Token::TokenName = tokenName;
    deamer::Token::IsNode = isNode;
    deamer::Token::CreateAst = createAst;
}

void deamer::Token::PrintToken()
{
    std::cout << TokenName << ' ';
}