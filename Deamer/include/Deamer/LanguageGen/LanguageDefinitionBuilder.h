/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_LANGUAGEGEN_LANGUAGEDEFINITIONBUILDER_H
#define DEAMER_LANGUAGEGEN_LANGUAGEDEFINITIONBUILDER_H

#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/Types/BitwiseEnum.h"
#include <vector>
#include <string>

namespace deamer
{
	class Token;
	class Type;
	class Node;
	class Rule;

	enum class TokenType_t;
	enum class TokenPermission_t;
	enum class TypeContinuation_t;
	
	class LanguageDefinitionBuilder
	{
	private:
		LanguageDefinition _language_definition = LanguageDefinition();
		
		TypeContinuation_t type_continuation = TypeContinuation_t::recursive;
		
		bool LanguageDefinitionContainsStartType() const;
	public:
		LanguageDefinitionBuilder() = default;
		LanguageDefinitionBuilder(LanguageDefinition& language_definition);
		~LanguageDefinitionBuilder() = default;

		void AddType(Type* type);
		Type* AddType(const std::string& tokenName);
		Type* AddType(const std::string& tokenName, BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission);
		Type* AddStartType(const std::string& tokenName);
		Type* AddGroupedType(const std::string& tokenName);
		void AddTokensToGroupedType(Type* grouped_token, std::vector<Token*> tokens);

		void AddNode(Node* node);
		Node* AddNode(const std::string& tokenName, const std::string& regex);
		Node* AddNode(const std::string& tokenName, const std::string& regex, BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission);
		Node* AddIgnorableNode(const std::string& tokenName, const std::string& regex);
		Node* AddDeletableNode(const std::string& tokenName, const std::string& regex);
		
		void AddRuleToType(Type* type, std::vector<Token*> rule_definition);
		void AddRuleToType(Type* type, Rule* rule_definition);

		void SetTypeContinuation(TypeContinuation_t typeContinuation);
		void SetLanguageName(const std::string& language_name);

		LanguageDefinition GetLanguageDefinition();
	};
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEDEFINITIONBUILDER_H