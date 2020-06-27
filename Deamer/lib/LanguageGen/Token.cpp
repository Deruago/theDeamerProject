#include <iostream>
#include <string>
#include "Deamer/LanguageGen/Token.h"

Token::Token(const std::string tokenName, const bool isNode, const bool createAst)
{
    Token::TokenName = tokenName;
    Token::IsNode = isNode;
    Token::CreateAst = createAst;
}

void Token::PrintToken()
{
    std::cout << TokenName << ' ';
}