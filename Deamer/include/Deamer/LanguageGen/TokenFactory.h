/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -July 2020 Thimo B�hmer
 */

/*
 * TokenFactory is used to create tokens.
 * It has specialised member functions and more generic ones.
 * It uses bitwise_enums for creating tokens.
 */

#ifndef DEAMER_LANGUAGEGEN_TOKENFACTORY_H
#define DEAMER_LANGUAGEGEN_TOKENFACTORY_H
#include "Deamer/Types/BitwiseEnum.h"
#include <string>

namespace deamer
{
	class Token;
	class Type;
	class Node;
	enum class TokenType_t;
	enum class TokenPermission_t;
	
	class TokenFactory
	{
	public:
		TokenFactory() = default;
		~TokenFactory() = default;
		
		//Token* MakeToken(BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const;
		Node* MakeNode(const std::string& tokenName, const std::string& regex) const; //alias for MakeTerminalSymbol
		Node* MakeNode(const std::string& tokenName, const std::string& regex, BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const; //alias for MakeTerminalSymbol
		Node* MakeIgnorableNode(const std::string& tokenName, const std::string& regex) const;
		Node* MakeDeletableNode(const std::string& tokenName, const std::string& regex) const;
		
		Type* MakeType(const std::string& tokenName) const; //alias for MakeNonTerminalSymbol
		Type* MakeType(const std::string& tokenName, BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const; //alias for MakeNonTerminalSymbol
		Type* MakeStartType(const std::string& tokenName) const; //alias for MakeNonTerminalSymbol
		Type* MakeStartType(const std::string& tokenName, BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const; //alias for MakeNonTerminalSymbol
		Type* MakeGroupedType(const std::string& tokenName) const; //alias for MakeNonTerminalSymbol
		Type* MakeGroupedType(const std::string& tokenName, BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const; //alias for MakeNonTerminalSymbol

		Type* MakeGroupedTypeUsingSingleTokens(const std::string& tokenName, const std::vector<Token*>& tokens) const;
		
		Node* MakeTerminalSymbol(const std::string& tokenName, const std::string& regex, BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const;
		Type* MakeNonTerminalSymbol(const std::string& tokenName, BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const;
	};
}

#endif //DEAMER_LANGUAGEGEN_TOKENFACTORY_H