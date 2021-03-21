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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_LEXICON_TERMINAL_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_LEXICON_TERMINAL_H

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/SpecialType.h"
#include "Deamer/Type/Memory/SafeReserve.h"
#include <string>

namespace deamer::language::type::definition::object::main
{
	/*! \class Terminal
	 *
	 *  Terminal symbol, used in lexicon definitions.
	 */
	class Terminal : public Base
	{
		friend deamer::type::SafeReserve<Terminal>;

	public:
		std::string Name;
		std::string Regex;
		SpecialType Special;

		Terminal(std::string name_, std::string regex_,
				 SpecialType special_ = SpecialType::Standard);

		Terminal(const Terminal& terminal);
		Terminal(Terminal&& terminal) noexcept;

		Terminal& operator=(const Terminal& terminal);
		Terminal& operator=(Terminal&& terminal) noexcept;

		~Terminal() = default;

	private:
		Terminal();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_LEXICON_TERMINAL_H
