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
		TypeContinuation_t type_continuation = TypeContinuation_t::recursive;
		LanguageDefinition* _language_definition = nullptr;
		
		bool LanguageDefinitionContainsStartType() const;
	public:
		LanguageDefinitionBuilder();
		~LanguageDefinitionBuilder() = default;

		void AddType(Type* type) const;
		Type* AddType(const std::string& tokenName) const;
		Type* AddType(const std::string& tokenName, BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const;
		Type* AddStartType(const std::string& tokenName) const;
		Type* AddGroupedType(const std::string& tokenName) const;
		void AddTokensToGroupedType(Type* grouped_token, std::vector<Token*> tokens) const;

		void AddNode(Node* node) const;
		Node* AddNode(const std::string& tokenName, const std::string& regex) const;
		Node* AddNode(const std::string& tokenName, const std::string& regex, BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const;
		Node* AddIgnorableNode(const std::string& tokenName, const std::string& regex) const;
		Node* AddDeletableNode(const std::string& tokenName, const std::string& regex) const;
		
		void AddRuleToType(Type* type, std::vector<Token*> rule_definition) const;
		void AddRuleToType(Type* type, Rule* rule_definition) const;

		void SetTypeContinuation(TypeContinuation_t typeContinuation);
		void SetLanguageName(const std::string& language_name) const;

		LanguageDefinition* GetLanguageDefinition() const;
	};
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEDEFINITIONBUILDER_H