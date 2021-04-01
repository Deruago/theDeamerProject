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

#ifndef DEAMER_PARSER_TYPE_BISON_PRODUCTIONRULEDECLARATION_H
#define DEAMER_PARSER_TYPE_BISON_PRODUCTIONRULEDECLARATION_H

#include "Deamer/File/Tool/Data.h"
#include "Deamer/Parser/Generator/Bison/Bison.h"
#include "Deamer/Parser/Type/Bison/ProductionRuleAction.h"

namespace deamer::parser::type::bison
{
	class ProductionRuleDeclaration : public file::tool::Data
	{
	private:
		const generator::bison::Bison::ReferenceType reference;

		const language::type::definition::object::main::NonTerminal* nonTerminal;
		const language::type::definition::object::main::ProductionRule* productionRule;

		ProductionRuleAction action;

		bool isFirstProductionRule;

	public:
		ProductionRuleDeclaration(
			const generator::bison::Bison::ReferenceType reference_,
			const language::type::definition::object::main::NonTerminal* nonTerminal_,
			const language::type::definition::object::main::ProductionRule* productionRule_,
			const bool isFirstProductionRule_);
		virtual ~ProductionRuleDeclaration() override = default;

	public:
		std::string Generate() const override;

	private:
		// return "| " if it is not the first rule.
		// else returns nothing.
		std::string GetRuleExtensionSymbol() const;

		std::string GetRuleHeader() const;
	};
}

#endif // DEAMER_PARSER_TYPE_BISON_PRODUCTIONRULEDECLARATION_H
