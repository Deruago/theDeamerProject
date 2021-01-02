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

#include "Deamer/LanguageAnalyzer/LanguagePrinter/LanguageDefinitionPrinter.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <vector>
#include <string>
#include <iostream>

void deamer::LanguageDefinitionPrinter::visit(Token& visited_type)
{
	std::cout << MakeIndentation(depth, 4) << visited_type.TokenName << std::endl;
}

void deamer::LanguageDefinitionPrinter::first_visit(Rule& visited_type)
{
}

void deamer::LanguageDefinitionPrinter::first_visit(Node& visited_type)
{
	std::cout << MakeIndentation(depth, 4) << visited_type.TokenName << std::endl;
}

void deamer::LanguageDefinitionPrinter::first_visit(Type& visited_type)
{
	std::cout << MakeIndentation(depth, 4) << visited_type.TokenName << std::endl;
}

void deamer::LanguageDefinitionPrinter::visit(Type& type)
{
	first_visit(type);
	for (Rule* rule : type.Rules)
	{
		depth++;
		for (Token* token : rule->Tokens)
			visit(*token);
		--depth;
	}
}

void deamer::LanguageDefinitionPrinter::visit(Node& node)
{
	first_visit(node);
}

void deamer::LanguageDefinitionPrinter::Print(LanguageDefinition& language_definition)
{
	dispatch(*language_definition.StartType);
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
