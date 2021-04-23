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

#include "Deamer/Parser/Type/Bison/ProductionRuleDeclaration.h"

deamer::parser::type::bison::ProductionRuleDeclaration::ProductionRuleDeclaration(
	const generator::bison::Bison::ReferenceType reference_,
	language::reference::LDO<language::type::definition::object::main::NonTerminal> nonTerminal_,
	language::reference::LDO<language::type::definition::object::main::ProductionRule> productionRule_,
	const bool isFirstProductionRule_)
	: reference(reference_),
	  nonTerminal(nonTerminal_),
	  productionRule(productionRule_),
	  action(reference_, nonTerminal_, productionRule_),
	  isFirstProductionRule(isFirstProductionRule_)
{
}

std::string deamer::parser::type::bison::ProductionRuleDeclaration::Generate() const
{
	return "\t" + GetRuleExtensionSymbol() + GetRuleHeader() + "{\n" + action.Generate() + "\t}\n";
}

std::string deamer::parser::type::bison::ProductionRuleDeclaration::GetRuleExtensionSymbol() const
{
	if (!isFirstProductionRule)
	{
		return "| ";
	}

	return "";
}

std::string deamer::parser::type::bison::ProductionRuleDeclaration::GetRuleHeader() const
{
	std::string ruleHeader;
	for (auto* ldo : productionRule->Tokens)
	{
		switch (ldo->Type_)
		{
		case language::type::definition::object::Type::Terminal: {
			ruleHeader +=
				static_cast<language::type::definition::object::main::Terminal*>(ldo)->Name;
			break;
		}
		case language::type::definition::object::Type::NonTerminal: {
			ruleHeader +=
				static_cast<language::type::definition::object::main::NonTerminal*>(ldo)->Name;
			break;
		}
		default:
			break;
		}
		ruleHeader += ' ';
	}

	return ruleHeader;
}
