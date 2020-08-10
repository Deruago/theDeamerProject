/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#include "Deamer/LanguageAnalyzer/LanguagePrinter/RulePrinter.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <iostream>


void deamer::RulePrinter::visit(Token& visited_type)
{
	std::cout << visited_type.TokenName << ' ';
}

void deamer::RulePrinter::visit(Rule& visited_type)
{
	std::cout << MakeIndentation(1, 4);
	for (Token* token : visited_type.Tokens)
	{
		visit(*token);
	}
	std::cout << std::endl;
}

void deamer::RulePrinter::visit(Node& visited_type)
{
}

void deamer::RulePrinter::visit(Type& visited_type)
{
	std::cout << MakeIndentation(0, 4) << visited_type.TokenName << std::endl;
}

void deamer::RulePrinter::last_visit(Type& type)
{
}

void deamer::RulePrinter::last_visit(Node& node)
{
}

void deamer::RulePrinter::Print(LanguageDefinition& language_definition)
{
	dispatch(*language_definition.StartType);
}
