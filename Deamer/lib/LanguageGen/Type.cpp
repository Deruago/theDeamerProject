#include <iostream>
#include <string>
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Type.h"

Type::Type(const std::string typeName) : Token::Token(typeName, false)
{
    return;
}

void Type::AddRule(Rule* newRule)
{
    Type::Rules.push_back(newRule);
}

void Type::PrintType()
{
    Type::PrintToken();
    Type::PrintRules();
}

void Type::PrintRules()
{
    for(auto i = 0; i < Rules.size(); i++)
    {
        Rules[i]->PrintRule();
    }
}