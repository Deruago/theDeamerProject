/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEGEN_TYPE_H
#define DEAMER_LANGUAGEGEN_TYPE_H


/*
This header describes the class implementation of Type. Type is a subclass of Token. And describes an object that exists of rules
*/

#include <string>
#include <vector>
#include "Deamer/Deamer.h"
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/TokenConstants.h"
#include "Deamer/LanguageGen/Rule.h"

namespace deamer
{
    class Type : public Token
    {

        public:
            std::vector<Rule*> Rules;
            Type(const std::string typeName, const bool createAst);
            Type(const std::string typeName);
            void AddRule(Rule* newRule);
            void PrintType();
            void PrintRules();
    };
}

#endif //DEAMER_LANGUAGEGEN_TYPE_H