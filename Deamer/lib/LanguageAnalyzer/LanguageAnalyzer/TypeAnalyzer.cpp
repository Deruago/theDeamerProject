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
#include <vector>
#include <map>

deamer::TypeAnalyzer::TypeAnalyzer(Type& type)
{
    type_ = type;
}

std::vector<deamer::Token*> deamer::TypeAnalyzer::GetVectorOfUniqueTokensDefiningThisType() const
{
    std::vector<Token*> token_vector;
    for (Rule* rule : type_.Rules)
        for (Token* token : rule->Tokens)
            if (!token->TokenPermission.has_flag(TokenPermission_t::ignore))
                AddTokenToVectorIfNotAlreadyInVector(token_vector, token);
    return token_vector;
}

std::vector<deamer::TokenAppearance> deamer::TypeAnalyzer::GetVectorOfMinimalAmountOfTokensUsedDefiningThisType() const
{
    std::map<Token*, unsigned> count_token;
    for (Rule* rule : type_.Rules)
    {
        std::map<Token*, unsigned> tmp_token_count;
        std::vector<Token*> tmp_token_vector;
        for (Token* token : rule->Tokens)
        {
	        const unsigned new_token_count = tmp_token_count[token] + 1;
            if (new_token_count == 1)
	        	tmp_token_vector.push_back(token);
            tmp_token_count[token] = new_token_count;
        }
    	for(Token* token_in_tmp_vector : tmp_token_vector)
    	{
            if (count_token[token_in_tmp_vector] < tmp_token_count[token_in_tmp_vector])
                count_token[token_in_tmp_vector] = tmp_token_count[token_in_tmp_vector];
    	}
    }
    std::vector<TokenAppearance> token_appearances;
	for(Token* token : GetVectorOfUniqueTokensDefiningThisType())
	{
        TokenAppearance token_appearance = { token, count_token[token]};
        token_appearances.push_back(token_appearance);
	}
    return token_appearances;
}

void deamer::TypeAnalyzer::AddTokenToVectorIfNotAlreadyInVector(std::vector<Token*>& tokens, Token* token) const
{
    for (Token* token_in_vector : tokens)
        if (token_in_vector == token)
            return;
    tokens.push_back(token);
}
