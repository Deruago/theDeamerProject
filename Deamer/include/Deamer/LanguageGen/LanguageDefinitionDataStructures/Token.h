/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

/*
This header describes the class implementation of Token. Which is the Base class for Tokens
*/

#ifndef DEAMER_LANGUAGEGEN_TOKEN_H
#define DEAMER_LANGUAGEGEN_TOKEN_H

#include "Deamer/Types/Visitable.h"
#include "Deamer/LanguageAnalyzer/LanguageVisitor/LanguageDefinitionVisitor.h"
#include "Deamer/Types/BitwiseEnum.h"
#include <string>
#include <vector>

namespace deamer
{
	class Type;
    enum class TokenType_t;
    enum class TokenPermission_t;
	
	class Token : public Visitable<Token, LanguageDefinitionVisitor>
    {
    protected:
        //Token(const std::string& tokenName, const bool isNode, const bool createAst);
        Token(const std::string& tokenName, const BitwiseEnum<TokenType_t> tokenType, const BitwiseEnum<TokenPermission_t> tokenPermission);
    public:
		std::string TokenName;

		unsigned TotalAmountOfTypesThatUsesThisToken;
        std::vector<Token*> BaseTokens;
        std::vector<Type*> BaseGroupTokens;
	
        BitwiseEnum<TokenType_t> TokenType;
        BitwiseEnum<TokenPermission_t> TokenPermission;

        void AddReferenceToTokenThatUsesThisToken();
        void RemoveReferenceThatUsedThisToken();
        void SetBaseGroupTokensIsVector(const bool cond);
    };
}

#endif //DEAMER_LANGUAGEGEN_TOKEN_H