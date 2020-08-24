/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -July 2020 Thimo B�hmer
 */

#include "Deamer/LanguageGen/LanguageDefinitionBuilder.h"
#include "Deamer/LanguageGen/RuleFactory.h"
#include "Deamer/LanguageGen/TokenFactory.h"
#include "Deamer/LanguageGen/UngroupableRuleExeption.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/RuleAnalyzer.h"

deamer::LanguageDefinitionBuilder::LanguageDefinitionBuilder(LanguageDefinition& language_definition)
{
	_language_definition = language_definition;
}

void deamer::LanguageDefinitionBuilder::AddType(Type* type)
{
	_language_definition.Types.push_back(type);
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
	Type* new_start_type = TokenFactory().MakeStartType(tokenName);
	AddType(new_start_type);
	_language_definition.StartType = new_start_type;
	return new_start_type;
}

deamer::Type* deamer::LanguageDefinitionBuilder::AddGroupedType(const std::string& tokenName)
{
	Type* new_type = TokenFactory().MakeGroupedType(tokenName);
	AddType(new_type);
	return new_type;
}

void deamer::LanguageDefinitionBuilder::AddTokensToGroupedType(Type* grouped_token, std::vector<Token*> tokens)
{
	for(Token* single_token : tokens)
	{
		AddRuleToType(grouped_token, RuleFactory().MakeGroupedRule(single_token));
		single_token->BaseTokens.push_back(grouped_token);
		single_token->BaseGroupTokens.push_back(grouped_token);
	}
}

void deamer::LanguageDefinitionBuilder::AddNode(Node* node)
{
	_language_definition.Nodes.push_back(node);
}

deamer::Node* deamer::LanguageDefinitionBuilder::AddNode(const std::string& tokenName, const std::string& regex)
{
	Node* new_node = TokenFactory().MakeNode(tokenName, regex);
	_language_definition.Nodes.push_back(new_node);
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

deamer::Node* deamer::LanguageDefinitionBuilder::AddDeletableNode(const std::string& tokenName,
	const std::string& regex)
{
	Node* new_node = TokenFactory().MakeDeletableNode(tokenName, regex);
	AddNode(new_node);
	return new_node;
}

void deamer::LanguageDefinitionBuilder::AddRuleToType(Type* type, std::vector<Token*> rule_definition)
{
	AddRuleToType(type, RuleFactory().MakeRule(rule_definition));
}

void deamer::LanguageDefinitionBuilder::AddRuleToType(Type* type, Rule* rule_definition)
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
	_language_definition.Rules.push_back(rule_definition);
}

void deamer::LanguageDefinitionBuilder::SetTypeContinuation(TypeContinuation_t typeContinuation)
{
	type_continuation = typeContinuation;
}

void deamer::LanguageDefinitionBuilder::SetLanguageName(const std::string& language_name)
{
	_language_definition.LanguageName = language_name;
}

deamer::LanguageDefinition deamer::LanguageDefinitionBuilder::GetLanguageDefinition() const
{
	return _language_definition;
}