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
	class Type;

	class Token
    {

        protected:
            Token(const std::string& tokenName, const bool isNode, const bool createAst);

        public:
            unsigned TotalAmountOfTypesThatUsesThisToken;
            std::vector<Token*> BaseTokens;
            bool IsNode;
            bool CreateAst;
            bool IsVector;
            std::string TokenName;
            void PrintToken();
            void AddBaseToken(Token* token);
            void AddReferenceToTokenThatUsesThisToken();
            void RemoveReferenceThatUsedThisToken();
            std::string MakeFunctionArgument();
            std::string MakeTypeCallAsClassField();
            std::string MakeTypeAsCtorInputVariable();
            std::string MakeConstructorTypeAssignment();
            std::string MakeTypeAsClassField();
    };
}

#endif //DEAMER_LANGUAGEGEN_TOKEN_H