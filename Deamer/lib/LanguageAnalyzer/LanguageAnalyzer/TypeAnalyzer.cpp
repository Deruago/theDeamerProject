/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/TypeAnalyzer.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/Datastructures/TokenAppearance.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/RuleFactory.h"
#include <vector>
#include <map>

deamer::TypeAnalyzer::TypeAnalyzer(Type& type)
{
	type_ = &type;
}

bool deamer::TypeAnalyzer::HasTypeEmptyRule() const
{
	for (Rule* rule : type_->Rules)
	{
		if (rule->RuleType.has_flag(RuleType_t::empty))
		{
			return true;
		}
	}
	return false;
}

std::vector<deamer::Token*> deamer::TypeAnalyzer::GetVectorOfUniqueTokensDefiningThisType() const
{
	std::vector<Token*> token_vector;
	for (Rule* rule : type_->Rules)
		for (Token* token : rule->Tokens)
			if (!token->TokenPermission.has_flag(TokenPermission_t::ignore) && type_ != token)
				AddTokenToVectorIfNotAlreadyInVector(token_vector, token);
	return token_vector;
}

std::vector<deamer::TokenAppearance> deamer::TypeAnalyzer::GetVectorOfMinimalAmountOfTokensUsedDefiningThisType() const
{
	std::map<Token*, unsigned> count_token;
	for (Rule* rule : type_->Rules)
	{
		std::map<Token*, unsigned> tmp_token_count;
		std::vector<Token*> tmp_token_vector;
		for (Token* token : rule->Tokens)
		{
			if (type_ == token)
				continue;
			const unsigned new_token_count = tmp_token_count[token] + 1;
			if (new_token_count == 1)
				tmp_token_vector.push_back(token);
			tmp_token_count[token] = new_token_count;
		}
		for (Token* token_in_tmp_vector : tmp_token_vector)
		{
			if (count_token[token_in_tmp_vector] < tmp_token_count[token_in_tmp_vector])
				count_token[token_in_tmp_vector] = tmp_token_count[token_in_tmp_vector];
		}
	}
	std::vector<TokenAppearance> token_appearances;
	for (Token* token : GetVectorOfUniqueTokensDefiningThisType())
	{
		TokenAppearance token_appearance = { token, count_token[token] };
		token_appearances.push_back(token_appearance);
	}
	return token_appearances;
}

std::vector<deamer::Rule*> deamer::TypeAnalyzer::GetVectorOfUniqueRulesApplyingIgnoredTokens() const
{
	std::vector<Rule*> unique_rules_without_ignored_tokens;
	for (Rule* tmp_rule : type_->Rules)
	{
		auto new_rule = CreateRule_Without_Ignored_Tokens(tmp_rule);
		if (IsThisRuleUniqueInVector(unique_rules_without_ignored_tokens, *new_rule))
			unique_rules_without_ignored_tokens.push_back(new_rule);
	}

	return unique_rules_without_ignored_tokens;
}

unsigned deamer::TypeAnalyzer::GetTokenTypesOccuringInType() const
{
	BitwiseEnum<TokenType_t> tokenTypesEncountered;
	BitwiseEnum<TokenPermission_t> tokenPermissionsEncountered;

	return GetTokenTypesOccuringInType(*type_, tokenTypesEncountered, tokenPermissionsEncountered);;
}

unsigned deamer::TypeAnalyzer::GetTokenTypesOccuringInType(const Type& type, BitwiseEnum<TokenType_t>& tokenType, BitwiseEnum<TokenPermission_t>& tokenPermission) const
{
	BitwiseEnum<TokenType_t> tokenTypesEncountered;
	BitwiseEnum<TokenPermission_t> tokenPermissionsEncountered;
	for (const Rule* rule : type.Rules)
	{
		for (const Token* token : rule->Tokens)
		{
			if (token->TokenType.has_flag(TokenType_t::grouped))
			{
				GetTokenTypesOccuringInType(*static_cast<const Type*>(token), tokenTypesEncountered, tokenPermissionsEncountered);
			}
			else
			{
				if (token->TokenType.has_flag(TokenType_t::standard))
				{
					// As some types are subsets of higher subsets we need to check which is activated
					if (token->TokenType.has_flag(TokenType_t::vector))
					{
						tokenTypesEncountered |= TokenType_t::vector;
					}
					else if (token->TokenType.has_flag(TokenType_t::standard))
					{
						tokenTypesEncountered |= TokenType_t::standard;
					}
				}
				else if (token->TokenPermission.has_flag(TokenPermission_t::node))
				{
					if (token->TokenPermission.has_flag(TokenPermission_t::delete_))
					{
						tokenPermissionsEncountered |= TokenPermission_t::delete_;
					}
					else if (token->TokenPermission.has_flag(TokenPermission_t::ignore))
					{
						tokenPermissionsEncountered |= TokenPermission_t::ignore;
					}
					else if (token->TokenPermission.has_flag(TokenPermission_t::node))
					{
						tokenPermissionsEncountered |= TokenPermission_t::node;
					}
				}
			}
		}
	}

	tokenType |= tokenTypesEncountered.enum_value();             //This has only active flags if non terminals occured
	tokenPermission |= tokenPermissionsEncountered.enum_value(); //This has active flags when non terminals occured
	// Note mixed terminals trigger both type list
	return tokenType.active_flags() + tokenPermission.active_flags();
}

deamer::Rule* deamer::TypeAnalyzer::CreateRule_Without_Ignored_Tokens(Rule* rule) const
{
	std::vector<Token*> tokens;
	bool encountered_ignorable_token = false;

	for (Token* token : rule->Tokens)
	{
		if (!token->TokenPermission.has_flag(TokenPermission_t::ignore) && token != type_)
			tokens.push_back(token);
		if (token->TokenPermission.has_flag(TokenPermission_t::ignore))
			encountered_ignorable_token = true;
	}
	if (encountered_ignorable_token)
		return RuleFactory().MakeDefaultRule(tokens);
	else
		return RuleFactory().MakeRule(tokens);
}

bool deamer::TypeAnalyzer::IsThisRuleUniqueInVector(const std::vector<Rule*>& rules, const Rule& rule) const
{
	for (Rule* unique_rule : rules)
	{
		if (AreRulesEqual(*unique_rule, rule))
			return false;
	}
	return true;
}

bool deamer::TypeAnalyzer::AreRulesEqual(const Rule& rule1, const Rule& rule2) const
{
	if (rule1.Tokens.size() != rule2.Tokens.size())
		return false;

	for (unsigned i = 0; i < rule1.Tokens.size(); i++)
	{
		if (rule1.Tokens[i] != rule2.Tokens[i])
			return false;
	}
	return true;
}

void deamer::TypeAnalyzer::AddTokenToVectorIfNotAlreadyInVector(std::vector<Token*>& tokens, Token* token) const
{
	for (Token* token_in_vector : tokens)
		if (token_in_vector == token)
			return;
	tokens.push_back(token);
}
