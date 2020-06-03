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

using namespace Deamer;

class Type : public Token
{

    public:
        std::vector<Rule*> Rules;
        Type(const std::string typeName);
        void AddRule(Rule* newRule);
        void PrintType();
        void PrintRules();
};

#endif //DEAMER_LANGUAGEGEN_TYPE_H