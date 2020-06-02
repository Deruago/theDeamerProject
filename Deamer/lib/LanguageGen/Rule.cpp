#include <iostream>
#include <string>
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Rule.h"

Rule::Rule(const std::vector<Token*> tokens)
{
    Rule::Tokens = tokens;
}

void Rule::PrintRule()
{
    for(auto i = 0; i < Tokens.size(); i++)
    {
        Tokens[i]->PrintToken();
    }
    std::cout << "\n";
}