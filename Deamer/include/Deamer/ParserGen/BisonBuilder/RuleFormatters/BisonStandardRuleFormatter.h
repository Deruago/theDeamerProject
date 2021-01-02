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

#ifndef DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONSTANDARDRULEFORMATTER_H
#define DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONSTANDARDRULEFORMATTER_H

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatter.h"

namespace deamer
{
	class BisonStandardRuleFormatter : public BisonRuleFormatter
	{
	private:
		std::string MakeExecutedCodeForProductionRule() const override;
		std::string FormatTypeRulePart() const;
		std::string MakeRuleExecutionPart() const;
	public:
		BisonStandardRuleFormatter(std::string& languageName, unsigned currentLineNumber, bool isFirstType, Type* currentType, Rule* currentRule);
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_RULEFORMATTERS_BISONSTANDARDRULEFORMATTER_H