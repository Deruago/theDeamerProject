/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEGEN_RULEFACTORY_H
#define DEAMER_LANGUAGEGEN_RULEFACTORY_H

#include <vector>

namespace deamer
{
	class Token;
	class Rule;
	
	class RuleFactory
	{
	public:
		RuleFactory() = default;
		~RuleFactory() = default;

		deamer::Rule* MakeRule() const;
		Rule* MakeRule(Token* token) const;
		Rule* MakeRule(const std::vector<Token*>& tokens) const;
		Rule* MakeGroupedRule(Token* token) const;
		deamer::Rule* MakeEmptyRule() const;
	};
}

#endif //DEAMER_LANGUAGEGEN_RULEFACTORY_H