/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include <string>

deamer::Type::Type(const std::string& typeName, const BitwiseEnum<TokenType_t> tokenType,
	const BitwiseEnum<TokenPermission_t> tokenPermission) : Token(typeName, tokenType, tokenPermission)
{
}