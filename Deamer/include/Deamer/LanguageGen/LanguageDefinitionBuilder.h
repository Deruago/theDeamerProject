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