/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEGEN_TYPE_H
#define DEAMER_LANGUAGEGEN_TYPE_H


 /*
 This header describes the class implementation of Type. Type is a subclass of Token. And describes an object that exists of rules
 */

#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Rule.h"
#include <vector>
#include <string>

namespace deamer
{
	class Type : public Token
	{
	public:
		std::vector<Rule*> Rules;

		//Type(const std::string& typeName, const bool createAst, const TokenType_t tokenType);
		Type(const std::string& typeName, const BitwiseEnum<TokenType_t> tokenType, const BitwiseEnum<TokenPermission_t> tokenPermission);
		void AddRule(Rule* newRule);
		void PrintType();
		void PrintRules();
		void AddTokenToVectorIfNotAlreadyInVector(std::vector<Token*>& tokens, Token* token);
		std::vector<Token*> GetVectorOfUniqueTokensDefiningThisType();
	};
}

#endif //DEAMER_LANGUAGEGEN_TYPE_H