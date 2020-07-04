#ifndef DEAMER_LANGUAGEGEN_RULE_H
#define DEAMER_LANGUAGEGEN_RULE_H

/*
This header describes the class implementation of Rule. Which is the base class for Rules.
*/

#include <string>
#include <vector>
#include "Deamer/Deamer.h"
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/TokenConstants.h"

namespace deamer
{
    class Rule
    {

        public:
            std::vector<Token*> Tokens;
            Rule(const std::vector<Token*> tokens);
            void PrintRule();
    };
}

#endif //DEAMER_LANGUAGEGEN_RULE_H