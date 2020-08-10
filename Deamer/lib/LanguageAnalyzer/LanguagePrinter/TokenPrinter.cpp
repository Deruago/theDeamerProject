/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/LanguageAnalyzer/LanguagePrinter/TokenPrinter.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <iostream>

void deamer::TokenPrinter::visit(Token& visited_type)
{
}

void deamer::TokenPrinter::first_visit(Rule& visited_type)
{
}

void deamer::TokenPrinter::first_visit(Node& visited_type)
{
	std::cout << MakeIndentation(0, 4) << visited_type.TokenName << std::endl;
}

void deamer::TokenPrinter::first_visit(Type& visited_type)
{
	std::cout << MakeIndentation(0, 4) << visited_type.TokenName << std::endl;
}

void deamer::TokenPrinter::visit(Type& type)
{
}

void deamer::TokenPrinter::visit(Node& node)
{
}

void deamer::TokenPrinter::Print(LanguageDefinition& language_definition)
{
	dispatch(*language_definition.StartType);
}
