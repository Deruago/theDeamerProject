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

#ifndef DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTENUMTOTYPE_H
#define DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTENUMTOTYPE_H

#include "Deamer/Language/Type/Definition/Object/Type.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/ProductionRule.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Precendence/ObjectPrecedence.h"

namespace deamer::language::convertor::definition
{
	/*! \class ObjectEnumToType
	 *
	 *	\brief This class is used to convert object enum types into typenames
	 *
	 *	\tparam T The enum value that needs to be converted to a typename
	 *
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<type::definition::object::Type T>
	class ObjectEnumToType
	{
	public:
		constexpr static auto value = type::definition::object::Type::Unknown;
		using type = void;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::Terminal>
	{
	public:
		constexpr static auto value = type::definition::object::Type::Terminal;
		using type = type::definition::object::main::Terminal;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::NonTerminal>
	{
	public:
		constexpr static auto value = type::definition::object::Type::NonTerminal;
		using type = type::definition::object::main::NonTerminal;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ProductionRule>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ProductionRule;
		using type = type::definition::object::main::ProductionRule;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ObjectPrecedence>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ObjectPrecedence;
		using type = type::definition::object::main::ObjectPrecedence;
	};

	template<type::definition::object::Type T>
	using ObjectEnumToType_t = typename ObjectEnumToType<T>::type;
}

#endif //DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTENUMTOTYPE_H