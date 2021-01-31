/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
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
        Token() = default;
        Token(const std::string& tokenName, const BitwiseEnum<TokenType_t> tokenType, const BitwiseEnum<TokenPermission_t> tokenPermission);
    public:
        virtual ~Token() = default;

        std::string TokenName;

		unsigned TotalAmountOfTypesThatUsesThisToken = 0;
        std::vector<Token*> BaseTokens;
        std::vector<Type*> BaseGroupTokens;
	
        BitwiseEnum<TokenType_t> TokenType;
        BitwiseEnum<TokenPermission_t> TokenPermission;

        void AddReferenceToTokenThatUsesThisToken();
        void RemoveReferenceThatUsedThisToken();
        void SetBaseGroupTokensIsVector(const bool cond);

		bool IsTerminal() const;
    };
}

#endif //DEAMER_LANGUAGEGEN_TOKEN_H