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

#include "Deamer/ParserGen/BisonBuilder/BisonRuleSectionFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatterFactory.h"
#include "Deamer/ParserGen/BisonBuilder/RuleFormatters/BisonRuleFormatter.h"
#include <string>
#include <sstream>


bool deamer::BisonRuleSectionFormatter::CurTypeIsFirstType() const
{
	return startType == currentType;
}

deamer::BisonRuleSectionFormatter::BisonRuleSectionFormatter(const std::string& lang_name)
{
	language_name_ = lang_name;
	currentType = nullptr;
	startType = nullptr;
}

std::string deamer::BisonRuleSectionFormatter::GetFormattedRuleSection() const
{
	//The last ';' is used to correctly end the last type.
	return ruleDeclarationPart;
}

void deamer::BisonRuleSectionFormatter::AddFirstType(Type*& type)
{
	startType = type;

	MakeType(type);
	ResetTypeInformation(type);
	for (Rule* rule : type->Rules)
		AddRule(rule);

	EndLastType();
}

void deamer::BisonRuleSectionFormatter::MakeType(Type*& type)
{
	ruleDeclarationPart += type->TokenName + ":\n";
}

void deamer::BisonRuleSectionFormatter::AddType(Type*& type)
{

	MakeType(type);
	ResetTypeInformation(type);
	for (Rule* rule : type->Rules)
		AddRule(rule);
	
	EndLastType();
}

void deamer::BisonRuleSectionFormatter::EndLastType()
{
	ruleDeclarationPart += ";\n\n";
}

void deamer::BisonRuleSectionFormatter::ResetTypeInformation(Type*& type)
{
	curRuleSizeOfType = type->Rules.size();
	CurrentLineNumber = 0;
	currentType = type;
}

void deamer::BisonRuleSectionFormatter::AddRule(Rule* currentRule)
{
	const std::unique_ptr<BisonRuleFormatter> ruleFormatter = BisonRuleFormatterFactory().MakeRuleFormatter(currentRule, language_name_, CurrentLineNumber, CurTypeIsFirstType(), currentType);
	ruleDeclarationPart += ruleFormatter->MakeRule();
	CurrentLineNumber++;
}