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

#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include <string>
#include <iostream>

//deamer::Token::Token(const std::string& tokenName, const bool isNode, const bool createAst)
//{
//    TokenName = tokenName;
//    IsNode = isNode;
//    CreateAst = createAst;
//}

deamer::Token::Token(const std::string& tokenName, const BitwiseEnum<TokenType_t> tokenType,
	const BitwiseEnum<TokenPermission_t> tokenPermission)
{
    TokenName = tokenName;
    TokenType = tokenType;
    TokenPermission = tokenPermission;
}

void deamer::Token::AddReferenceToTokenThatUsesThisToken()
{
    TotalAmountOfTypesThatUsesThisToken++;
}

void deamer::Token::RemoveReferenceThatUsedThisToken()
{
    --TotalAmountOfTypesThatUsesThisToken;
}

void deamer::Token::SetBaseGroupTokensIsVector(const bool cond)
{
    for (Type* type : BaseGroupTokens)
    {
        if (type->TokenType != TokenType_t::start)
        {
            type->SetBaseGroupTokensIsVector(cond);
            type->TokenType.set_flag(TokenType_t::vector, cond);
        }
    }
}