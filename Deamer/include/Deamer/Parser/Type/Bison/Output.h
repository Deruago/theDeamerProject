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

#ifndef DEAMER_PARSER_TYPE_FILE_BISON_OUTPUT_H
#define DEAMER_PARSER_TYPE_FILE_BISON_OUTPUT_H

#include "Deamer/Parser/Generator/Bison/Bison.h"
#include "Deamer/Parser/Type/Bison/ActionSection.h"
#include "Deamer/Parser/Type/Bison/IncludeSection.h"
#include "Deamer/Parser/Type/Bison/ProductionRuleSection.h"
#include "Deamer/Parser/Type/Bison/TokenDeclarationSection.h"
#include "Deamer/Parser/Type/Bison/UnionSection.h"
#include <string>

namespace deamer::parser::type::bison
{
	class Output
	{
	private:
		const generator::bison::Bison::ReferenceType reference;

		IncludeSection includeSection;
		TokenDeclarationSection tokenDeclarationSection;
		UnionSection unionSection;

		ProductionRuleSection productionRuleSection;

		ActionSection actionSection;

	public:
		Output(const generator::bison::Bison::ReferenceType reference_);
		~Output() = default;

	public:
		void AddTerminal(
			language::reference::LDO<language::type::definition::object::main::Terminal> terminal);

		void AddNonTerminal(
			language::reference::LDO<language::type::definition::object::main::NonTerminal>
				nonTerminal);

		std::string Generate() const;
	};
}

#endif // DEAMER_PARSER_TYPE_FILE_BISON_OUTPUT_H
