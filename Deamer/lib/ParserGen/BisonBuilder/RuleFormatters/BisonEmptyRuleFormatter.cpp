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

#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonEmptyRuleFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"

deamer::BisonEmptyRuleFormatter::BisonEmptyRuleFormatter(std::string& languageName, unsigned currentLineNumber,
                                                         bool isFirstType, Type* currentType, Rule* currentRule) : BisonRuleFormatter(languageName, currentLineNumber, isFirstType, currentType, currentRule)
{
}

std::string deamer::BisonEmptyRuleFormatter::MakeExecutedCodeForProductionRule() const
{
	if (CurrentType->TokenType.has_flag(TokenType_t::vector))
		return "          $$ = new std::vector<" + TypeToClassName(CurrentType) + "*>();\n";
	else
		return FormatTypeRulePart();
}

std::string deamer::BisonEmptyRuleFormatter::FormatTypeRulePart() const
{
	return MakeRuleExecutionPart() + MakeOutputCodeWhenNodeIsStartType();
}

std::string deamer::BisonEmptyRuleFormatter::MakeRuleExecutionPart() const
{
	return MakeAstType(LanguageName) + AddArgumentsToAstType(LanguageName);
}