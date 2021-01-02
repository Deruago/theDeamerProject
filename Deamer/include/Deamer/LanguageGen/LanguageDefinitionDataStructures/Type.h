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

#ifndef DEAMER_LANGUAGEGEN_TYPE_H
#define DEAMER_LANGUAGEGEN_TYPE_H


 /*
 This header describes the class implementation of Type. Type is a subclass of Token. And describes an object that exists of rules
 */

#include "Deamer/Types/Visitable.h"
#include "Deamer/LanguageAnalyzer/LanguageVisitor/LanguageDefinitionVisitor.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include <vector>
#include <string>

namespace deamer
{
	class Type : public Token, public Visitable<Type, LanguageDefinitionVisitor>
	{
	public:
		std::vector<Rule*> Rules;
		Type() = default;
		Type(const std::string& typeName, const BitwiseEnum<TokenType_t> tokenType, const BitwiseEnum<TokenPermission_t> tokenPermission);
		virtual ~Type() = default;
	};
}

#endif //DEAMER_LANGUAGEGEN_TYPE_H