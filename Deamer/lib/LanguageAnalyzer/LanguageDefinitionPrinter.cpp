/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/LanguageAnalyzer/LanguageDefinitionPrinter.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LanguageGen/Rule.h"
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Type.h"
#include "Deamer/LanguageGen/Node.h"
#include <iostream>
#include <stack>
#include <set>

void deamer::LanguageDefinitionPrinter::PrintTree(LanguageDefinition& language_definition) const
{
	PrintCompleteType(language_definition.StartType, 0);
}

bool deamer::LanguageDefinitionPrinter::TypeAlreadyVisited(const std::vector<Type*>& visited_types, Token* new_type) const
{
	for (Type* visited_type : visited_types)
		if (visited_type == new_type)
			return true;
	return false;
}

std::string deamer::LanguageDefinitionPrinter::MakeIndent(unsigned indent) const
{
	std::string indent_str;
	for(unsigned i = 0; i < indent; i++)
	{
		indent_str += ' ';
	}
	return indent_str;
}

std::string deamer::LanguageDefinitionPrinter::MakeIndentation(unsigned depth, unsigned indent) const
{
	std::string indentation;
	for(unsigned i = 0; i < depth; i++)
	{
		indentation += MakeIndent(indent);
	}
	return indentation;
}

void deamer::LanguageDefinitionPrinter::PrintCompleteType(std::vector<Type*> visited_types, Type* type, unsigned indent) const
{
	visited_types.push_back(type);
	for (Rule* rule : type->Rules)
	{
		std::cout << MakeIndentation(indent, 4) << type->TokenName << std::endl;
		if (rule->RuleType.is_flag_not_set(RuleType_t::empty))
			PrintCompleteRule(visited_types, rule, indent + 1);
	}
}

void deamer::LanguageDefinitionPrinter::PrintCompleteToken(Token* token, unsigned indent) const
{
	std::cout << MakeIndentation(indent, 4) << token->TokenName << std::endl;
}

void deamer::LanguageDefinitionPrinter::PrintCompleteRule(std::vector<Type*>& visited_types, Rule* rule, unsigned indent) const
{
	for (Token* token_in_rule : rule->Tokens)
	{
		if (!TypeAlreadyVisited(visited_types, token_in_rule) && !token_in_rule->TokenPermission.has_flag(TokenPermission_t::node))
			PrintCompleteType(visited_types, static_cast<Type*>(token_in_rule), indent);
		else
			PrintCompleteToken(token_in_rule, indent);
	}
}

void deamer::LanguageDefinitionPrinter::PrintCompleteType(Type* type, unsigned indent) const
{
	std::vector<Type*> visited_types;
	PrintCompleteType(visited_types, type, indent);
}

















void deamer::LanguageDefinitionPrinter::PrintAllTokens(LanguageDefinition& language_definition) const
{
}

void deamer::LanguageDefinitionPrinter::PrintAllRules(LanguageDefinition& language_definition) const
{
}

void deamer::LanguageDefinitionPrinter::PrintAllNodes(LanguageDefinition& language_definition) const
{
}

void deamer::LanguageDefinitionPrinter::PrintAllGroupedTypes(LanguageDefinition& language_definition) const
{
}

void deamer::LanguageDefinitionPrinter::PrintAllIgnoredNodes(LanguageDefinition& language_definition) const
{
}

void deamer::LanguageDefinitionPrinter::PrintAllIgnoredTypes(LanguageDefinition& language_definition) const
{
}
