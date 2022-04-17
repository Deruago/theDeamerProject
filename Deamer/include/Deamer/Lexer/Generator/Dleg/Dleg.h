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

#ifndef DEAMER_LEXER_GENERATOR_DLEG_H
#define DEAMER_LEXER_GENERATOR_DLEG_H

#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Lexer/Generator/Base.h"
#include <array>
#include <vector>

namespace deamer::lexer::generator::dleg
{
	class Dleg : public Base
	{
	public:
		using ReferenceType = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar>;

	private:
		const ReferenceType reference;
		const std::string name;

	public:
		Dleg(ReferenceType reference_);
		~Dleg() override = default;

	public:
		deamer::file::tool::Output Generate() override;

	private:
		std::string ConvertTransitionTableToCode();
		std::vector<std::tuple<std::array<std::size_t, 256>, bool, std::set<std::string>>>
		ConstructAsciiTransitionTable();
		std::string ExternalCmake();
		deamer::language::type::definition::object::main::Terminal*
		GetStrongestFlavor(std::set<std::string> flavors);
	};
}

#endif // DEAMER_LEXER_GENERATOR_DLEG_H
