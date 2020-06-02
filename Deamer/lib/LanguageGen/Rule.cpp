#include <string>
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Rule.h"

Rule::Rule(const std::vector<Token*> tokens)
{
    Rule::Tokens = tokens;
}