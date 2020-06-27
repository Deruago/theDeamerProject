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

    protected:
        Token(const std::string tokenName, const bool isNode, const bool createAst);

    public:
        bool IsNode;
        bool CreateAst;
        std::string TokenName;
        void PrintToken();
};

#endif //DEAMER_LANGUAGEGEN_TOKEN_H