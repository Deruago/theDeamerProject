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

#ifndef DEAMER_AST_TYPE_CPP_ENUM_H
#define DEAMER_AST_TYPE_CPP_ENUM_H

#include "Deamer/File/Tool/File.h"
#include "Deamer/Language/Reference/LDO.h"
#include "Deamer/Language/Reference/PropertyDefinition.h"

namespace deamer::ast::type::cpp
{
	/*!	\class Enum
	 *
	 *	\brief Generates a file with all the possible used AST nodes
	 */
	class Enum
	{
	private:
		using ReferenceType = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar>;

		ReferenceType reference;
		std::string languageName;

		std::vector<language::reference::LDO<language::type::definition::object::main::Terminal>>
			terminals;

		std::vector<language::reference::LDO<language::type::definition::object::main::NonTerminal>>
			nonTerminals;

	public:
		Enum(ReferenceType reference_);
		~Enum() = default;

	public:
		deamer::file::tool::File Generate() const;

		void AddTerminal(
			language::reference::LDO<language::type::definition::object::main::Terminal> terminal);
		void AddNonTerminal(
			language::reference::LDO<language::type::definition::object::main::NonTerminal>
				nonTerminal);

	private:
		std::string GenerateEnumerations() const;
	};
}

#endif // DEAMER_AST_TYPE_CPP_ENUM_H
