/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstNodeFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"

deamer::AstNodeFormatter::AstNodeFormatter(const std::string& language_name)
{
	language_name_ = language_name;
}

std::string deamer::AstNodeFormatter::MakeClassName(const Token* token) const
{
	if (token->TokenType.has_flag(TokenType_t::start))
		return "AstTree_" + token->TokenName;
	else
		return "AstNode_" + token->TokenName;
}
