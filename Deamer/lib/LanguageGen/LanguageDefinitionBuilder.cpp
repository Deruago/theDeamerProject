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

#include "Deamer/LanguageGen/LanguageDefinitionBuilder.h"
#include "Deamer/LanguageGen/RuleFactory.h"
#include "Deamer/LanguageGen/TokenFactory.h"
#include "Deamer/LanguageGen/UngroupableRuleExeption.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/RuleAnalyzer.h"


deamer::LanguageDefinitionBuilder::LanguageDefinitionBuilder()
{
	_language_definition = new LanguageDefinition();
}

void deamer::LanguageDefinitionBuilder::AddType(Type* type) const
{
	_language_definition->AddType(type);
}

deamer::Type* deamer::LanguageDefinitionBuilder::AddType(const std::string& tokenName) const
{
	Type* new_type = TokenFactory().MakeType(tokenName);
	AddType(new_type);
	return new_type;
}

deamer::Type* deamer::LanguageDefinitionBuilder::AddType(const std::string& tokenName,
	BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const
{
	Type* new_type = TokenFactory().MakeType(tokenName, tokenType, tokenPermission);
	AddType(new_type);
	return new_type;
}

deamer::Type* deamer::LanguageDefinitionBuilder::AddStartType(const std::string& tokenName) const
{
	Type* new_start_type = TokenFactory().MakeStartType(tokenName);
	AddType(new_start_type);
	_language_definition->StartType = new_start_type;
	return new_start_type;
}

deamer::Type* deamer::LanguageDefinitionBuilder::AddGroupedType(const std::string& tokenName) const
{
	Type* new_type = TokenFactory().MakeGroupedType(tokenName);
	AddType(new_type);
	return new_type;
}

void deamer::LanguageDefinitionBuilder::AddTokensToGroupedType(Type* grouped_token, std::vector<Token*> tokens) const
{
	for(Token* single_token : tokens)
	{
		AddRuleToType(grouped_token, RuleFactory().MakeGroupedRule(single_token));
		//single_token->BaseTokens.push_back(grouped_token);
		//single_token->BaseGroupTokens.push_back(grouped_token);
	}
}

void deamer::LanguageDefinitionBuilder::AddNode(Node* node) const
{
	_language_definition->AddNode(node);
}

deamer::Node* deamer::LanguageDefinitionBuilder::AddNode(const std::string& tokenName, const std::string& regex) const
{
	Node* new_node = TokenFactory().MakeNode(tokenName, regex);
	_language_definition->AddNode(new_node);
	return new_node;
}

deamer::Node* deamer::LanguageDefinitionBuilder::AddNode(const std::string& tokenName, const std::string& regex,
	BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission) const
{
	Node* new_node = TokenFactory().MakeNode(tokenName, regex, tokenType, tokenPermission);
	AddNode(new_node);
	return new_node;
}

deamer::Node* deamer::LanguageDefinitionBuilder::AddIgnorableNode(const std::string& tokenName,
	const std::string& regex) const
{
	Node* new_node = TokenFactory().MakeIgnorableNode(tokenName, regex);
	AddNode(new_node);
	return new_node;
}

deamer::Node* deamer::LanguageDefinitionBuilder::AddDeletableNode(const std::string& tokenName,
	const std::string& regex) const
{
	Node* new_node = TokenFactory().MakeDeletableNode(tokenName, regex);
	AddNode(new_node);
	return new_node;
}

void deamer::LanguageDefinitionBuilder::AddRuleToType(Type* type, std::vector<Token*> rule_definition) const
{
	AddRuleToType(type, RuleFactory().MakeRule(rule_definition));
}

void deamer::LanguageDefinitionBuilder::AddRuleToType(Type* type, Rule* rule_definition) const
{
	if (rule_definition == nullptr)
	{
		rule_definition = RuleFactory().MakeRule(); // creates empty rule
	}
	else if (type->TokenType.has_flag(TokenType_t::grouped) && !type->TokenType.has_flag(TokenType_t::start))
	{
		if (RuleAnalyzer().IsGroupable(*rule_definition))
		{
			rule_definition->RuleType.set_flag(RuleType_t::grouped);
			rule_definition->Tokens[0]->BaseTokens.push_back(type);
			rule_definition->Tokens[0]->BaseGroupTokens.push_back(type);
		}
		else
			throw UngroupableRuleException();
	}
	else if (type_continuation == TypeContinuation_t::vector)
	{
		if (RuleAnalyzer().IsVectorisable(*type, *rule_definition))
		{
			rule_definition->RuleType.set_flags({ RuleType_t::vectorised, RuleType_t::recursive });
			type->TokenType.set_flag(TokenType_t::vector);
		}
	}
	type->Rules.push_back(rule_definition);
	_language_definition->AddRule(rule_definition);
}

void deamer::LanguageDefinitionBuilder::SetTypeContinuation(TypeContinuation_t typeContinuation)
{
	type_continuation = typeContinuation;
}

void deamer::LanguageDefinitionBuilder::SetLanguageName(const std::string& language_name) const
{
	_language_definition->LanguageName = language_name;
}

deamer::LanguageDefinition* deamer::LanguageDefinitionBuilder::GetLanguageDefinition() const
{
	if (!LanguageDefinitionContainsStartType())
	{
		_language_definition->GetTypes()[0]->TokenType.set_flag(TokenType_t::start);
		_language_definition->StartType = _language_definition->GetTypes()[0];
	}
	return _language_definition;
}

bool deamer::LanguageDefinitionBuilder::LanguageDefinitionContainsStartType() const
{
	bool contains_start_type = false;
	for (Type* type_ : _language_definition->GetTypes())
		if (type_->TokenType.has_flag(TokenType_t::start))
			contains_start_type = true;
	return contains_start_type;
}
