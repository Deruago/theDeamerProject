/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEGEN_RULE_H
#define DEAMER_LANGUAGEGEN_RULE_H

/*
This header describes the class implementation of Rule. Which is the base class for Rules.
*/

#include "Deamer/LanguageGen/Token.h"
#include "Deamer/ParserGen/BisonBuilder/BisonBuilder.h"
#include <vector>

namespace deamer
{
    class Rule
    {
        public:
            std::vector<Token*> Tokens;
            RuleType_t RuleType = RuleType_t::standard;
            Rule(const std::vector<Token*>& tokens);
            void PrintRule();
            bool IsEmpty() const;
    };
}

#endif //DEAMER_LANGUAGEGEN_RULE_H