#include <iostream>
#include <string>
#include "Deamer/LanguageGen/Token.h"

Token::Token(const std::string tokenName, const bool isNode)
{
    Token::TokenName = tokenName;
    Token::IsNode = isNode;
}

void Token::PrintToken()
{
    std::cout << TokenName << ' ';
}