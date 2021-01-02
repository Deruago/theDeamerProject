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

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatterFactory.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatter.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonEmptyRuleFormatter.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonGroupedRuleFormatter.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonVectorisedRuleFormatter.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonStandardRuleFormatter.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include <memory>


std::unique_ptr<deamer::BisonRuleFormatter> deamer::BisonRuleFormatterFactory::MakeRuleFormatter(
	Rule* rule, std::string& languageName, unsigned currentLineNumber, bool isFirstType,
	Type* currentType) const
{
	BitwiseEnum<RuleType_t> ruleType = rule->RuleType;
	if(ruleType.has_flag(RuleType_t::empty))
	{
		return std::make_unique<BisonEmptyRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType, rule);
	}
	if(ruleType.has_flag(RuleType_t::standard))
	{
		return std::make_unique<BisonStandardRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType, rule);
	}
	if (ruleType.has_flag(RuleType_t::grouped))
	{
		return std::make_unique<BisonGroupedRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType, rule);
	}
	if (ruleType.has_flag(RuleType_t::vectorised))
	{
		return std::make_unique<BisonVectorisedRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType, rule);
	}
	return std::make_unique<BisonStandardRuleFormatter>(languageName, currentLineNumber, isFirstType, currentType, rule);
}
