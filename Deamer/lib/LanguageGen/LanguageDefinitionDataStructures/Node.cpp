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

#include <string>
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Node.h"

//deamer::Node::Node(const std::string& nodeName, const std::string& regex, const bool createAst) : Token(nodeName, true, createAst)
//{
//    Regex = regex;
//}

deamer::Node::Node(const std::string& typeName, const std::string& regex, const BitwiseEnum<TokenType_t> tokenType,
	const BitwiseEnum<TokenPermission_t> tokenPermission) : Token(typeName, tokenType, tokenPermission)
{
	Regex = regex;
}
