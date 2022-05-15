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

#include "Deamer/Parser/Type/Antlr/ParserDefinition.h"
#include "Deamer/Language/Analyzer/Main/Grammar/ProductionRule.h"
#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Template/Parser/Antlr/ParserDefinitionTemplate.h"

deamer::parser::type::antlr::ParserDefinition::ParserDefinition(ReferenceType reference_)
	: reference(reference_)
{
}

std::string deamer::parser::type::antlr::ParserDefinition::Generate() const
{
	const auto language_name =
		reference.GetDefinition<language::type::definition::property::Type::Identity>()
			.GetName()
			->value;

	auto parserDefinition = templates::antlr::parser::ParserDefinitionTemplate();
	parserDefinition.language_name_->Set(language_name);

	for (language::reference::LDO<language::type::definition::object::main::NonTerminal>
			 nonterminal :
		 reference.GetDefinition<language::type::definition::property::Type::Grammar>()
			 .NonTerminals)
	{
		parserDefinition.production_rule_declaration_->variable_field_->Clear();
		parserDefinition.nonterminal_name_->Set(nonterminal->Name);

		const auto& productionRules = nonterminal->ProductionRules;

		if (productionRules.empty())
		{
			continue;
		}

		parserDefinition.production_rule_->Set(GetProductionRuleName(productionRules[0]));
		parserDefinition.production_rule_declaration_->Set(
			parserDefinition.first_production_rule_declaration_);
		parserDefinition.production_rule_declaration_->ExpandVariableField();

		for (auto i = 1; i < productionRules.size(); i++)
		{
			parserDefinition.production_rule_->Set(GetProductionRuleName(productionRules[i]));
			parserDefinition.production_rule_declaration_->Set(
				parserDefinition.second_production_rule_declaration_);
			parserDefinition.production_rule_declaration_->ExpandVariableField();
		}

		parserDefinition.nonterminal_declaration_->ExpandVariableField();
	}

	return parserDefinition.GetOutput();
}

std::string deamer::parser::type::antlr::ParserDefinition::GetProductionRuleName(
	language::reference::LDO<language::type::definition::object::main::ProductionRule> ldo) const
{
	::std::string name;
	for (language::reference::LDO<::deamer::language::type::definition::object::Base> base :
		 ldo->Tokens)
	{
		switch (base->Type_)
		{
		case language::type::definition::object::Type::Terminal: {
			const auto terminal =
				base.Promote<language::type::definition::object::main::Terminal>();
			name += terminal->Name + ' ';
			break;
		}
		case language::type::definition::object::Type::NonTerminal: {
			const auto nonTerminal =
				base.Promote<language::type::definition::object::main::NonTerminal>();
			name += nonTerminal->Name + ' ';
			break;
		}
		default:
			break;
		}
	}

	return name;
}
