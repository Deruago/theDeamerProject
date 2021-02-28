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

#ifndef DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETOBJECTENUMSFROMPROPERTYTYPE_H
#define DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETOBJECTENUMSFROMPROPERTYTYPE_H

#include "Deamer/Language/Type/Definition/Object/Type.h"
#include "Deamer/Language/Type/Definition/Property/Main/Lexicon.h"
#include "Deamer/Language/Type/Definition/Property/Main/Grammar.h"

namespace deamer::language::validator::definition
{
	template<typename T>
	class GetObjectEnumsFromPropertyType
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Unknown };
		using type = void;
	};
	
	template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Lexicon>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Terminal };
		using type = type::definition::property::main::Lexicon;
	};

	template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Grammar>
	{
	public:
		constexpr static auto value = {
			type::definition::object::Type::NonTerminal,
			type::definition::object::Type::ProductionRule
		};
		using type = type::definition::property::main::Lexicon;
	};
}

#endif //DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETOBJECTENUMSFROMPROPERTYTYPE_H