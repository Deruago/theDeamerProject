#ifndef DEAMER_LANGUAGEGEN_TOKEN_H
#define DEAMER_LANGUAGEGEN_TOKEN_H


/*
This header describes the class implementation of Token. Which is the Base class for Tokens
*/

#include <string>
#include "Deamer/Deamer.h"
#include "Deamer/LanguageGen/TokenConstants.h"

using namespace Deamer;

class Token
{
    bool IsNode;

    protected:
        Token(const std::string tokenName, const bool isNode);

    public:
        std::string TokenName;
};

#endif //DEAMER_LANGUAGEGEN_TOKEN_H