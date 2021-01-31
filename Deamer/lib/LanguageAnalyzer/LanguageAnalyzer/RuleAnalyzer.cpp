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

#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/RuleAnalyzer.h"

#include <stack>


#include "Deamer/LanguageAnalyzer/LanguagePrinter/TokenPrinter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"


bool deamer::RuleAnalyzer::IsEmpty(Rule& rule) const
{
	return rule.Tokens.empty();
}

bool deamer::RuleAnalyzer::IsGroupable(Rule& rule) const
{
	return rule.Tokens.size() == 1;
}

bool deamer::RuleAnalyzer::IsVectorisable(Rule& rule) const
{
	if (rule.Tokens.empty())
		return false;
	for (Token* token : rule.Tokens)
		if (!token->TokenPermission.has_flag(TokenPermission_t::node))
			for (Rule* rule_in_type : static_cast<Type*>(token)->Rules)
				if (rule_in_type == &rule)
					return true;
	return false;
}

bool deamer::RuleAnalyzer::DoesRuleHaveMultipleCallsToTypeDirectlyAfterEachOther(const Rule& rule, const Type& type) const
{
	bool lastTimeFoundSameType = false;
	for (auto* Token : rule.Tokens)
	{
		bool foundSameType = false;
		if (Token == &type)
		{
			foundSameType = true;
		}

		if (lastTimeFoundSameType && foundSameType) // if we found the NT twice after each other
		{
			return true;
		}

		lastTimeFoundSameType = foundSameType;
	}

	return false;
}

bool deamer::RuleAnalyzer::IsVectorisable(Type& type, Rule& rule) const
{
	if (rule.Tokens.empty())
		return false;
	return rule.Tokens[0] == &type || rule.Tokens[rule.Tokens.size() - 1] == &type;
}

deamer::Rule deamer::RuleAnalyzer::FlattenRule(const Rule& rule, const Type& terminatingType) const
{
	std::vector<Token*> tokens;
	std::vector<Token*> visitedTokens;
	FlattenRule(rule, tokens, terminatingType, visitedTokens);
	
	return Rule(tokens);
}

void deamer::RuleAnalyzer::FlattenRule(const Rule& rule, std::vector<Token*>& tokens, const Type& terminatingType, std::vector<Token*>& visitedTokens) const
{
	for (auto* token : rule.Tokens)
	{
		bool alreadyVisited = false;
		for (auto* visitedToken : visitedTokens)
		{
			if (visitedToken == token)
			{
				alreadyVisited = true;
				break;
			}
		}
		
		if (token->IsTerminal()
			|| token == &terminatingType
			|| alreadyVisited)
		{
			tokens.push_back(token);
			continue;
		}

		const auto tmpRules = static_cast<Type*>(token)->Rules;
		if (tmpRules.empty())
			continue;

		visitedTokens.push_back(token);
		FlattenRule(*tmpRules[0], tokens, terminatingType, visitedTokens);
		visitedTokens.pop_back();
	}
}
