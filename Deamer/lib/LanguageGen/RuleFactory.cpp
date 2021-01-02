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

#include "Deamer/LanguageGen/RuleFactory.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"

deamer::Rule* deamer::RuleFactory::MakeRule() const
{
	Rule* new_rule = new Rule();
	new_rule->RuleType.set_flag(RuleType_t::empty);
	return new_rule;
}

deamer::Rule* deamer::RuleFactory::MakeRule(Token* token) const
{
	return new Rule({ token });
}

deamer::Rule* deamer::RuleFactory::MakeRule(const std::vector<deamer::Token*>& tokens) const
{
	Rule* new_rule = new Rule(tokens);
	if (tokens.empty())
		new_rule->RuleType.set_flag(RuleType_t::empty);
	return new_rule;
}

deamer::Rule* deamer::RuleFactory::MakeGroupedRule(Token* token) const
{
	Rule* new_grouped_rule = new Rule({ token });
	new_grouped_rule->RuleType.set_flag(RuleType_t::grouped);
	return new_grouped_rule;
}

deamer::Rule* deamer::RuleFactory::MakeEmptyRule() const
{
	Rule* new_empty_rule = new Rule();
	new_empty_rule->RuleType.set_flag(RuleType_t::empty);
	return new_empty_rule;
}

deamer::Rule* deamer::RuleFactory::MakeDefaultRule(const std::vector<Token*>& tokens)
{
	return new Rule(tokens);
}

