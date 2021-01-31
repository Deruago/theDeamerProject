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

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_RULEANALYZER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_RULEANALYZER_H
#include <stack>

#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"

namespace deamer
{
	class Type;
	class Rule;

	class RuleAnalyzer
	{
	public:
		RuleAnalyzer() = default;
		~RuleAnalyzer() = default;

		bool IsEmpty(Rule& rule) const;
		bool IsGroupable(Rule& rule) const;

		// The type is needed to assert if the rule is vectorisable, As the type indicates recursion O(n)
		// Prioritise this member function when possible. As the other overload needs to check each type in the rule recursively
		bool IsVectorisable(Type& type, Rule& rule) const;
		// This is an inefficent overload. This uses the types within the rule to check if the types have this rule. O(n^2)
		// Only use this member function if you dont have direct access to the type containing this rule.
		bool IsVectorisable(Rule& rule) const;

		// e.g. NT1 NT1 NT2, or NT3 NT1 NT2 NT1 NT1 NT3
		bool DoesRuleHaveMultipleCallsToTypeDirectlyAfterEachOther(const Rule& rule, const Type& type) const;

		// Flatten rule, makes 1 big rule where NT's are substituted for their first production rule
		Rule FlattenRule(const Rule& rule, const Type& terminatingType) const;
	private:
		void FlattenRule(const Rule& rule, std::vector<Token*>& tokens, const Type& terminatingType, std::vector<Token*>& visitedTokens) const;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_RULEANALYZER_H