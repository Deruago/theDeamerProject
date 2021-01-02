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

#ifndef DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONGROUPEDRULEFORMATTER_H
#define DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONGROUPEDRULEFORMATTER_H

#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatter.h"
#include "Deamer/Types/BitwiseEnum.h"

namespace deamer
{
	class BisonGroupedRuleFormatter : public BisonRuleFormatter
	{
	private:
		std::string MakeExecutedCodeForMixedGroup(const Token& currentToken) const;
		
		std::string MakeExecutedCodeForPureGroup(const Token& currentToken) const;
		std::string MakeExecutedCodeForPureGroupStandard(const Token& currentToken) const;
		std::string MakeExecutedCodeForPureGroupVector(const Token& currentToken) const;
		std::string MakeExecutedCodeForPureGroupNode(const Token& currentToken) const;
		std::string MakeExecutedCodeForPureGroupIgnore(const Token& currentToken) const;
		std::string MakeExecutedCodeForPureGroupDelete(const Token& currentToken) const;
		
		std::string MakeNonTerminalCode(const Token& currentToken) const;
		std::string MakeVectorCode(const Token& currentToken) const;
		std::string MakeTerminalCode(const Token& currentToken) const;
		std::string MakeIgnoreCodeWithoutGroupObject(const Token& currentToken) const;
		std::string MakeIgnoreCodeWithGroupObject(const Token& currentToken) const;

		std::string MakeExecutedCodeForProductionRule() const override;
		bool isPureGroup = false; //Does it exists of 1 group?
		BitwiseEnum<TokenType_t> groupNonTerminalTypes;    //The types occuring in our group
		BitwiseEnum<TokenPermission_t> groupTerminalTypes; //The types occuring in our group
	public:
		BisonGroupedRuleFormatter(std::string& languageName, unsigned currentLineNumber, bool isFirstType, Type* currentType, Rule* currentRule);
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONGROUPEDRULEFORMATTER_H