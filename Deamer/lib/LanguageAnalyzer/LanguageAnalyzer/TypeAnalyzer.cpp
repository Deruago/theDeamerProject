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
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include <vector>

std::vector<deamer::Token*> deamer::TypeAnalyzer::GetVectorOfUniqueTokensDefiningThisType(Type& type) const
{
    std::vector<Token*> token_vector;
    for (Rule* rule : type.Rules)
        for (Token* token : rule->Tokens)
            if (!token->TokenPermission.has_flag(TokenPermission_t::ignore))
                AddTokenToVectorIfNotAlreadyInVector(token_vector, token);
    return token_vector;
}

void deamer::TypeAnalyzer::AddTokenToVectorIfNotAlreadyInVector(std::vector<Token*>& tokens, Token* token) const
{
    for (Token* token_in_vector : tokens)
        if (token_in_vector == token)
            return;
    tokens.push_back(token);
}
