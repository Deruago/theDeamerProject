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

#ifndef DEAMER_PARSERGEN_BISONBUILDER_H
#define DEAMER_PARSERGEN_BISONBUILDER_H

#include "Deamer/ParserGen/ParserBuilder.h"
#include "Deamer/ParserGen/BisonBuilder/BisonRuleSectionFormatter.h"
#include <string>

namespace deamer
{
	class Node;
	class Type;
	class Rule;
	class LanguageDefinition;
	
	class BisonBuilder : public ParserBuilder
	{
		BisonRuleSectionFormatter ruleFormatter = BisonRuleSectionFormatter("");
		std::string tokenDeclarationPart;
		std::string typeDeclarationPart;
		Type* firstType;
		bool IsTypeFirstType(Type* type) const;
	public:
		BisonBuilder(const LanguageDefinition* langDef);
		~BisonBuilder() = default;
		void AddNode(Node* node) override;
		void AddType(Type* type) override;
		void AddRule(Rule* rule) override;
		bool FinishBuild() override;
		bool StartBuild() override;
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_H