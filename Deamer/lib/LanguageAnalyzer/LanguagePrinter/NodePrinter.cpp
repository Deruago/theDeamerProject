/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/LanguageAnalyzer/LanguagePrinter/NodePrinter.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <iostream>

void deamer::NodePrinter::visit(Token& visited_type)
{
}

void deamer::NodePrinter::visit(Rule& visited_type)
{
}

void deamer::NodePrinter::visit(Node& visited_type)
{
	std::cout << MakeIndentation(0, 4) << visited_type.TokenName << std::endl;
}

void deamer::NodePrinter::visit(Type& visited_type)
{
}

void deamer::NodePrinter::last_visit(Type& type)
{
}

void deamer::NodePrinter::last_visit(Node& node)
{
}

void deamer::NodePrinter::Print(LanguageDefinition& language_definition)
{
	dispatch(*language_definition.StartType);
}
