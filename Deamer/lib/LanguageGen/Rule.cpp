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
#include "Deamer/LanguageGen/Rule.h"

deamer::Rule::Rule(const std::vector<deamer::Token*> tokens)
{
    Rule::Tokens = tokens;
}

void deamer::Rule::PrintRule()
{
    for(auto i = 0; i < Tokens.size(); i++)
    {
        Tokens[i]->PrintToken();
    }
    std::cout << "\n";
}