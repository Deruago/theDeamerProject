/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include <string>
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Node.h"

//deamer::Node::Node(const std::string& nodeName, const std::string& regex, const bool createAst) : Token(nodeName, true, createAst)
//{
//    Regex = regex;
//}

deamer::Node::Node(const std::string& typeName, const std::string& regex, const BitwiseEnum<TokenType_t> tokenType,
	const BitwiseEnum<TokenPermission_t> tokenPermission) : Token(typeName, tokenType, tokenPermission)
{
	Regex = regex;
}
