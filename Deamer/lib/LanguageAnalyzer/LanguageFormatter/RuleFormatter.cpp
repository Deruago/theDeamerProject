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

#include "Deamer/LanguageAnalyzer/LanguageFormatter/RuleFormatter.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"

std::string deamer::RuleFormatter::MakeConstructorArguments(Token* token_subject, Rule& rule)
{
	/*
	std::string args;
	unsigned arg_count_implemented = 0;
	for (auto& Token : rule.Tokens)
	{
		if (Token->TokenPermission.has_flag(TokenPermission_t::ignore))
			continue;
		if (Token == token_subject)
			continue;
		if (arg_count_implemented == 0)
		{
			args += Token->MakeFunctionArgument();
			arg_count_implemented++;
		}
		else
		{
			args += ", " + Token->MakeFunctionArgument();
			arg_count_implemented++;
		}
	}

	return args;
	//*/
}

std::string deamer::RuleFormatter::MakeConstructorPrototype(Token* token_subject, Rule& rule)
{
	return token_subject->TokenName + "(" + MakeConstructorArguments(token_subject, rule) + ")";
}

std::string deamer::RuleFormatter::MakeConstructors(Token* token_subject, Rule& rule)
{
	/*
	std::string constructor_assignments;
	for (Token* token : rule.Tokens)
		if (!token->TokenPermission.has_flag(TokenPermission_t::ignore) && token != token_subject)
		{
			constructor_assignments += "    " + token->MakeConstructorTypeAssignment() + ";\n";
			if (token->TokenType.has_flag(TokenType_t::vector))
			{
				constructor_assignments += "    for(AstNode_" + token->TokenName + "* _" + token->MakeTypeCallAsClassField() + " : *" + token->MakeTypeAsCtorInputVariable() + ")\n";
				constructor_assignments += "        AstNodes.push_back(_" + token->MakeTypeCallAsClassField() + ");\n";
			}
			else
			{
				constructor_assignments += "    AstNodes.push_back(" + token->MakeTypeAsCtorInputVariable() + ");\n";
			}
		}

	return constructor_assignments;
	//*/
}

std::string deamer::RuleFormatter::MakeConstructor(Token* token, Rule& rule)
{
	return "{\n" + MakeConstructors(token, rule) + "}\n";
}