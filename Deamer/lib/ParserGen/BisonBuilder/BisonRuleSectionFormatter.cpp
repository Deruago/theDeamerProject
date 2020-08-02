/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/BisonRuleSectionFormatter.h"
#include "Deamer/LanguageGen/Rule.h"
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Type.h"
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
	return ruleDeclarationPart + ';';
}

void deamer::BisonRuleSectionFormatter::AddFirstType(Type*& type)
{
	startType = type;

	MakeType(type);
	ResetTypeInformation(type);
}

void deamer::BisonRuleSectionFormatter::MakeType(Type*& type)
{
	ruleDeclarationPart += type->TokenName + ":\n";
}

void deamer::BisonRuleSectionFormatter::EndLastType()
{
	ruleDeclarationPart += ";\n\n";
}

void deamer::BisonRuleSectionFormatter::AddType(Type*& type)
{
	EndLastType();

	MakeType(type);
	ResetTypeInformation(type);
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