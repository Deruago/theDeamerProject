/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEGEN_TOKEN_H
#define DEAMER_LANGUAGEGEN_TOKEN_H


/*
This header describes the class implementation of Token. Which is the Base class for Tokens
*/

#include <string>
#include <vector>

namespace deamer
{
    class Token
    {

        protected:
            Token(const std::string& tokenName, const bool isNode, const bool createAst);

        public:
            std::vector<Token*> BaseTokens;
            bool IsNode;
            bool CreateAst;
            std::string TokenName;
            void PrintToken();
            void AddBaseToken(Token* token);
    };
}

#endif //DEAMER_LANGUAGEGEN_TOKEN_H