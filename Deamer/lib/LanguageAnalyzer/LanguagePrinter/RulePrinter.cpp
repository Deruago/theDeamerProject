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

#include "Deamer/LanguageAnalyzer/LanguagePrinter/RulePrinter.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <iostream>


void deamer::RulePrinter::visit(Token& visited_type)
{
	std::cout << visited_type.TokenName << ' ';
}

void deamer::RulePrinter::first_visit(Rule& visited_type)
{
	std::cout << MakeIndentation(1, 4);
	for (Token* token : visited_type.Tokens)
	{
		visit(*token);
	}
	std::cout << std::endl;
}

void deamer::RulePrinter::first_visit(Node& visited_type)
{
}

void deamer::RulePrinter::first_visit(Type& visited_type)
{
	std::cout << MakeIndentation(0, 4) << visited_type.TokenName << std::endl;
}

void deamer::RulePrinter::visit(Type& type)
{
}

void deamer::RulePrinter::visit(Node& node)
{
}

void deamer::RulePrinter::Print(LanguageDefinition& language_definition)
{
	dispatch(*language_definition.StartType);
}
