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