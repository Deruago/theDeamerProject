/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/LanguageGen/LanguageDefinitionBuilder.h"

#include "Deamer/LanguageGen/RuleFactory.h"
#include "Deamer/LanguageGen/TokenFactory.h"
#include "Deamer/LanguageGen/UngroupableRuleExeption.h"

void deamer::LanguageDefinitionBuilder::AddType(Type* type)
{
	language_definition.Types.push_back(type);
}

void deamer::LanguageDefinitionBuilder::AddNode(Node* node)
{
	language_definition.Nodes.push_back(node);
}

deamer::Type* deamer::LanguageDefinitionBuilder::AddType(const std::string& tokenName)
{
	Type* new_type = TokenFactory().MakeType(tokenName);
	AddType(new_type);
	return new_type;
}

deamer::Type* deamer::LanguageDefinitionBuilder::AddType(const std::string& tokenName,
	BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission)
{
	Type* new_type = TokenFactory().MakeType(tokenName, tokenType, tokenPermission);
	AddType(new_type);
	return new_type;
}

deamer::Type* deamer::LanguageDefinitionBuilder::AddStartType(const std::string& tokenName)
{
	Type* new_type = TokenFactory().MakeStartType(tokenName);
	AddType(new_type);
	return new_type;
}

deamer::Type* deamer::LanguageDefinitionBuilder::AddGroupedType(const std::string& tokenName)
{
	Type* new_type = TokenFactory().MakeGroupedType(tokenName);
	AddType(new_type);
	return new_type;
}

deamer::Node* deamer::LanguageDefinitionBuilder::AddNode(const std::string& tokenName, const std::string& regex)
{
	Node* new_node = TokenFactory().MakeNode(tokenName, regex);
	language_definition.Nodes.push_back(new_node);
	return new_node;
}

deamer::Node* deamer::LanguageDefinitionBuilder::AddNode(const std::string& tokenName, const std::string& regex,
	BitwiseEnum<TokenType_t> tokenType, BitwiseEnum<TokenPermission_t> tokenPermission)
{
	Node* new_node = TokenFactory().MakeNode(tokenName, regex, tokenType, tokenPermission);
	AddNode(new_node);
	return new_node;
}

deamer::Node* deamer::LanguageDefinitionBuilder::AddIgnorableNode(const std::string& tokenName,
	const std::string& regex)
{
	Node* new_node = TokenFactory().MakeIgnorableNode(tokenName, regex);
	AddNode(new_node);
	return new_node;
}

void deamer::LanguageDefinitionBuilder::AddRuleToType(Type* type, std::vector<Token*> rule_definition)
{
	AddRuleToType(type, RuleFactory().MakeRule(rule_definition));
}

void deamer::LanguageDefinitionBuilder::AddRuleToType(Type* type, Rule* rule_definition)
{
	if (type->TokenType.has_flag(TokenType_t::grouped))
	{
		if (RuleIsGroupable(type, rule_definition))
			rule_definition->RuleType = RuleType_t::grouped;
		else
			throw UngroupableRuleException();
	}
	else if (type_continuation == TypeContinuation_t::vector)
	{
		if (RuleIsVectorisable(type, rule_definition))
		{
			rule_definition->RuleType = RuleType_t::vectorised;
			type->TokenType.set_flag(TokenType_t::vector);
		}
	}
	
	type->Rules.push_back(rule_definition);
	language_definition.Rules.push_back(rule_definition);
}

void deamer::LanguageDefinitionBuilder::SetTypeContinuation(TypeContinuation_t typeContinuation)
{
	type_continuation = typeContinuation;
}

deamer::LanguageDefinition deamer::LanguageDefinitionBuilder::GetLanguageDefinition() const
{
	return language_definition;
}


bool deamer::LanguageDefinitionBuilder::RuleIsGroupable(Type* type, Rule* rule) const
{
	return rule->Tokens.size() == 1;
}

bool deamer::LanguageDefinitionBuilder::RuleIsVectorisable(Type* type, Rule* rule) const
{
	if (rule->Tokens.empty())
		return false;
	return rule->Tokens[0] == type || rule->Tokens[rule->Tokens.size()] == type;
}