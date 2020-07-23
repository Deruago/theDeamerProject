/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -June 2020 Thimo Bohmer
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/ParserGen/BisonBuilder/BisonBuilder.h"
#include "Deamer/ParserGen/BisonBuilder/BisonParserFormatter.h"
#include "Deamer/ParserGen/BisonBuilder/BisonRuleSectionFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Node.h"
#include "Deamer/LanguageGen/Rule.h"
#include "Deamer/LanguageGen/Type.h"
#include <sstream>
#include <ostream>


deamer::BisonBuilder::BisonBuilder(LanguageDefinition* langDef)
{
	BisonBuilder::langDef = langDef;
	firstType = nullptr;
	IsFirstType = true;
	ruleFormatter = BisonRuleSectionFormatter(langDef->GetLanguageName());
}

void deamer::BisonBuilder::AddNode(Node* node)
{
	std::ostringstream oss;
	oss << "%token " << node->TokenName << '\n';
	tokenDeclarationPart += oss.str();

	std::ostringstream oss2;
	oss2 << "%type <DeamerNode> " << node->TokenName << '\n';
	typeDeclarationPart += oss2.str();
}

void deamer::BisonBuilder::AddType(Type* type)
{
	std::ostringstream oss;
	oss << "%type <ASTNODE> " << type->TokenName << '\n';
	typeDeclarationPart += oss.str();

	if(IsFirstType)
	{
		IsFirstType = false;
		firstType = type;
		ruleFormatter.AddFirstType(type);
	}
	else
		ruleFormatter.AddType(type);
}

/*
 *
bool deamer::BisonBuilder::IsCurrentTypeGrouped() const
{
	return currentType->GroupedType;
}

void deamer::BisonBuilder::MakeGroupedRule(Rule* rule)
{
	ruleDeclarationPart += FormatGroupedRule(rule);
}

std::string deamer::BisonBuilder::FormatGroupedRule(Rule* rule)
{
	std::ostringstream oss;
	oss << "    ";

	AddCorrectNotationForNewRule(oss);

	WriteRule(rule, &oss);
	WriteGroupedRuleModificationPart(rule, &oss);

	oss << '\n';
	return oss.str();
}

void deamer::BisonBuilder::WriteGroupedRuleModificationPart(Rule* rule, std::ostringstream* oss) const
{
	const std::string LanguageName = langDef->GetLanguageName();
	FormatTypeGroupedRulePart(rule, oss, LanguageName);
}

void deamer::BisonBuilder::FormatTypeGroupedRulePart(Rule* rule, std::ostringstream* oss, const std::string&
	LanguageName) const
{
	*oss << "{\n";
	MakeGroupRuleExecutionPart(LanguageName, rule, oss);
	MakeOutputCodeWhenNodeIsStartType(oss);
	*oss << "    }";
}

void deamer::BisonBuilder::MakeGroupRuleExecutionPart(const std::string& LanguageName, Rule* rule, std::ostringstream* oss) const
{
	//This makes sure we dont create random ',' when nothing can be added.
	if (!rule->IsEmpty())
	{
		MakeAstType(LanguageName, oss);
		AddArgumentsToAstType(LanguageName, rule, oss);
	}
}

*/

void deamer::BisonBuilder::AddRule(Rule* rule)
{
	ruleFormatter.AddRule(rule);
}

bool deamer::BisonBuilder::FinishBuild()
{
	const auto ruleDeclarationPart = ruleFormatter.GetFormattedRuleSection();
	std::ostringstream ParserFunctions;
	const BisonParserFormatter ParserFormatter(langDef->GetLanguageName(), firstType->TokenName,
	                                            tokenDeclarationPart, typeDeclarationPart,
	                                            ruleDeclarationPart);
	Output = ParserFormatter.MakeParserFile(ParserFunctions);
	
	return true;
}

bool deamer::BisonBuilder::StartBuild()
{
	return true;
}