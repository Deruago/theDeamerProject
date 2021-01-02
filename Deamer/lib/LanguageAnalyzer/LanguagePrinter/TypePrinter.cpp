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
