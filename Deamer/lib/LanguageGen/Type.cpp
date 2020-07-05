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
#include "Deamer/LanguageGen/Type.h"

deamer::Type::Type(const std::string typeName, const bool createAst) : deamer::Token::Token(typeName, false, createAst)
{
}

deamer::Type::Type(const std::string typeName) : deamer::Type::Type(typeName, true)
{
}


void deamer::Type::AddRule(deamer::Rule* newRule)
{
    deamer::Type::Rules.push_back(newRule);
}

void deamer::Type::PrintType()
{
    deamer::Type::PrintToken();
    deamer::Type::PrintRules();
}

void deamer::Type::PrintRules()
{
    for(auto i = 0; i < Rules.size(); i++)
    {
        Rules[i]->PrintRule();
    }
}