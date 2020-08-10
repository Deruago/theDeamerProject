/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/LanguageAnalyzer/LanguagePrinter/TypePrinter.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <iostream>

void deamer::TypePrinter::visit(Token& visited_type)
{
}

void deamer::TypePrinter::first_visit(Rule& visited_type)
{
}

void deamer::TypePrinter::first_visit(Node& visited_type)
{
}

void deamer::TypePrinter::first_visit(Type& visited_type)
{
	std::cout << MakeIndentation(0, 4) << visited_type.TokenName << std::endl;
}

void deamer::TypePrinter::visit(Type& type)
{
}

void deamer::TypePrinter::visit(Node& node)
{
}

void deamer::TypePrinter::Print(LanguageDefinition& language_definition)
{
	dispatch(*language_definition.StartType);
}
