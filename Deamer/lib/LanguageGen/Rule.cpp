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