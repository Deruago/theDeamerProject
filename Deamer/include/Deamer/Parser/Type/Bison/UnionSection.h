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

#ifndef DEAMER_PARSER_TYPE_BISON_UIONSECTION_H
#define DEAMER_PARSER_TYPE_BISON_UIONSECTION_H

#include "Deamer/File/Tool/Data.h"
#include "Deamer/Parser/Generator/Bison/Bison.h"

namespace deamer::parser::type::bison
{
	class UnionSection : public file::tool::Data
	{
	private:
		const generator::bison::Bison::ReferenceType reference;

		std::vector<language::type::definition::object::main::Terminal> terminals;
		std::vector<language::type::definition::object::main::NonTerminal> nonTerminals;

	public:
		UnionSection(const generator::bison::Bison::ReferenceType reference_);
		virtual ~UnionSection() override = default;

	public:
		void AddTerminal(const language::type::definition::object::main::Terminal& terminal);

		void
		AddNonterminal(const language::type::definition::object::main::NonTerminal& nonTerminal);
		void GenerateASTUnionTypes(std::string& output, const std::string& languageName) const;
		std::string Generate() const override;

	private:
		std::string
		GetObjectFullType(const language::type::definition::object::main::Terminal& terminal) const;

		std::string GetObjectFullType(
			const language::type::definition::object::main::NonTerminal& nonTerminal) const;
	};
}

#endif // DEAMER_PARSER_TYPE_BISON_UIONSECTION_H
