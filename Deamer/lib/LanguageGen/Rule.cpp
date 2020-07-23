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
#include "Deamer/LanguageGen/Rule.h"

deamer::Rule::Rule(const std::vector<Token*>& tokens)
{
    Tokens = tokens;
}

void deamer::Rule::PrintRule()
{
    for (auto& Token : Tokens)
    {
	    Token->PrintToken();
    }
    std::cout << "\n";
}

bool deamer::Rule::IsEmpty() const
{
    return Tokens.empty();
}
