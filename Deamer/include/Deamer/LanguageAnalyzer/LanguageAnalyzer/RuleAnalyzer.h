/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_RULEANALYZER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_RULEANALYZER_H

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
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEANALYZER_RULEANALYZER_H