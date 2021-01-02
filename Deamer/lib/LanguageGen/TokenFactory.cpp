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

#include "Deamer/LanguageGen/TokenFactory.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/RuleFactory.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Node.h"

deamer::Node* deamer::TokenFactory::MakeNode(const std::string& tokenName, const std::string& regex) const
{
	BitwiseEnum<TokenType_t> tokenType;
	tokenType.set_flag(TokenType_t::none);

	BitwiseEnum<TokenPermission_t> tokenPermission;
	tokenPermission.set_flags({ TokenPermission_t::node });
	return MakeTerminalSymbol(tokenName, regex, tokenType, tokenPermission);
}

deamer::Node* deamer::TokenFactory::MakeNode(const std::string& tokenName, const std::string& regex,
                                             BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const
{
	return MakeTerminalSymbol(tokenName, regex, tokenType, tokenPermission);
}

deamer::Node* deamer::TokenFactory::MakeIgnorableNode(const std::string& tokenName, const std::string& regex) const
{
	BitwiseEnum<TokenType_t> tokenType;
	tokenType.set_flag(TokenType_t::none);

	BitwiseEnum<TokenPermission_t> tokenPermission;
	tokenPermission.set_flags({ TokenPermission_t::node, TokenPermission_t::ignore});
	return MakeTerminalSymbol(tokenName, regex, tokenType, tokenPermission);
}

deamer::Node* deamer::TokenFactory::MakeDeletableNode(const std::string& tokenName, const std::string& regex) const
{
	BitwiseEnum<TokenType_t> tokenType;
	tokenType.set_flag(TokenType_t::none);

	BitwiseEnum<TokenPermission_t> tokenPermission;
	tokenPermission.set_flags({ TokenPermission_t::node, TokenPermission_t::ignore, TokenPermission_t::delete_});
	return MakeTerminalSymbol(tokenName, regex, tokenType, tokenPermission);
}

deamer::Type* deamer::TokenFactory::MakeType(const std::string& tokenName) const
{
	BitwiseEnum<TokenType_t> tokenType;
	tokenType.set_flag(TokenType_t::standard);
	BitwiseEnum<TokenPermission_t> tokenPermission;

	return MakeNonTerminalSymbol(tokenName, tokenType, tokenPermission);
}

deamer::Type* deamer::TokenFactory::MakeType(const std::string& tokenName, BitwiseEnum<TokenType_t> tokenType,
	BitwiseEnum<TokenPermission_t> tokenPermission) const
{
	return MakeNonTerminalSymbol(tokenName, tokenType, tokenPermission);
}

deamer::Type* deamer::TokenFactory::MakeStartType(const std::string& tokenName) const
{
	BitwiseEnum<TokenType_t> tokenType;
	tokenType.set_flag(TokenType_t::start);
	tokenType.set_flag(TokenType_t::standard);
	BitwiseEnum<TokenPermission_t> tokenPermission;

	return MakeNonTerminalSymbol(tokenName, tokenType, tokenPermission);
}

deamer::Type* deamer::TokenFactory::MakeStartType(const std::string& tokenName, BitwiseEnum<TokenType_t> tokenType,
                                                  BitwiseEnum<TokenPermission_t> tokenPermission) const
{
	tokenType.set_flag(TokenType_t::start);
	return MakeNonTerminalSymbol(tokenName, tokenType, tokenPermission);
}

deamer::Type* deamer::TokenFactory::MakeGroupedType(const std::string& tokenName) const
{
	BitwiseEnum<TokenType_t> tokenType;
	tokenType.set_flag(TokenType_t::standard);
	tokenType.set_flag(TokenType_t::grouped);
	BitwiseEnum<TokenPermission_t> tokenPermission;

	return MakeNonTerminalSymbol(tokenName, tokenType, tokenPermission);
}

deamer::Type* deamer::TokenFactory::MakeGroupedType(const std::string& tokenName, BitwiseEnum<TokenType_t> tokenType,
	BitwiseEnum<TokenPermission_t> tokenPermission) const
{
	tokenType.set_flag(TokenType_t::grouped);
	return MakeNonTerminalSymbol(tokenName, tokenType, tokenPermission);
}

deamer::Type* deamer::TokenFactory::MakeGroupedTypeUsingSingleTokens(const std::string& tokenName,
                                                                     const std::vector<Token*>& tokens) const
{
	Type* new_grouped_type = MakeGroupedType(tokenName);
	for(Token* single_token : tokens)
		new_grouped_type->Rules.push_back(RuleFactory().MakeGroupedRule(single_token));

	return new_grouped_type;
}

deamer::Node* deamer::TokenFactory::MakeTerminalSymbol(const std::string& tokenName, const std::string& regex,
                                                       BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const
{
	tokenPermission.set_flag(TokenPermission_t::node);
	return new Node(tokenName, regex, tokenType, tokenPermission);
}

deamer::Type* deamer::TokenFactory::MakeNonTerminalSymbol(const std::string& tokenName,
	BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const
{
	tokenPermission.clear_flag(TokenPermission_t::node);
	return new Type(tokenName, tokenType, tokenPermission);
}
