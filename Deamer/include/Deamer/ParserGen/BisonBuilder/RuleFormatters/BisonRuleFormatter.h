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

#ifndef DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONRULEFORMATTER_H
#define DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONRULEFORMATTER_H

#include "Deamer/ParserGen/BisonBuilder/BisonRuleSectionFormatter.h"
#include <string>

namespace deamer
{
	class Token;
	class Rule;

	class BisonRuleFormatter
	{
	private:
		std::string MakeRuleProductionDefinition() const;
		virtual std::string MakeExecutedCodeForProductionRule() const = 0;

		std::string MakeBeginExecutedCodePartForProductionRule() const;
		std::string MakeEndExecutedCodePartForProductionRule() const;
	protected:
		std::string LanguageName = "";
		unsigned CurrentLineNumber;
		Type* CurrentType = nullptr;
		Rule* CurrentRule;

		bool CurrentTokenIsNode(Token* CurrentToken) const;
		bool CurrentTokenHasAnAstNode(Token* CurrentToken) const;
		bool CurrentTypeIsTheFirstType() const;
		std::string MakeArgumentReferenceVariable(int& ArgumentCount) const;
		std::string MakeArgument(const std::string& LanguageName, int& ArgumentCount, Token* CurrentToken) const;
		std::string AddFirstArgument(const std::string& LanguageName, int& j) const;
		std::string MakeNewAstNode(const std::string& LanguageName, int ArgumentCount,
		                           Token* CurrentToken) const;
		std::string AddRestOfAllArguments(const std::string& LanguageName, int ArgumentCount) const;
		std::string MakeAstType(const std::string& LanguageName) const;
		std::string AddArgumentsToAstType(const std::string& LanguageName) const;
		std::string MakeAstTree(const std::string& LanguageName) const;
		std::string MakeAddToMainTypeLine() const;
		unsigned GetRecursiveTypeLocationInRule() const;
		std::string MakeVectorCreationLogic() const;
		std::string TypeToClassName(Type* type) const;
		std::string MakeEndAddToMainTypeLine() const;
		std::string MakeAstNode(const std::string& LanguageName) const;
		std::string MakeAstNode(const std::string& LanguageName, const std::string& TokenName) const;
		std::string MakeOutputCodeForAstTree() const;
		std::string MakeOutputCodeWhenNodeIsStartType() const;
		std::string MakeProductionRuleNotation() const;
		std::string FormatRule() const;
	public:
		BisonRuleFormatter(std::string& languageName, unsigned currentLineNumber, bool isFirstType, Type* currentType, Rule* currentRule);
		virtual ~BisonRuleFormatter() = default;
		std::string MakeRule() const;
		const char EndProductionRule() const;
		const char* MakeIndentation() const;
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONRULEFORMATTER_H