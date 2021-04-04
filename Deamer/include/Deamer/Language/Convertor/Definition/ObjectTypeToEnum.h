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

#ifndef DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTTYPETOENUM_H
#define DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTTYPETOENUM_H

#include "Deamer/Language/Type/Definition/Object/Type.h"

namespace deamer::language::type::definition::object
{
	class Base;
}

namespace deamer::language::type::definition::object::main
{
	class ObjectAssociativity;
	class Generate;
	class GenerateArgument;
	class Integrate;
	class NonTerminal;
	class ProductionRule;
	class Name;
	class Terminal;
	class ObjectPrecedence;
}

namespace deamer::language::convertor::definition
{
	/*! \class ObjectTypeToEnum
	 *
	 *	\brief This class is used to convert object types into enumerated values.
	 *
	 *	\tparam T The type that needs to be converted to a enumerated value.
	 *
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<typename T>
	class ObjectTypeToEnum
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Unknown;
		using type = void;
	};

	template<typename T>
	class ObjectTypeToEnum<const T> : public ObjectTypeToEnum<T>
	{
	};

	template<typename T>
	class ObjectTypeToEnum<volatile T> : public ObjectTypeToEnum<T>
	{
	};

	template<typename T>
	class ObjectTypeToEnum<const volatile T> : public ObjectTypeToEnum<T>
	{
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::Terminal>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Terminal;
		using type = type::definition::object::main::Terminal;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::NonTerminal>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::NonTerminal;
		using type = type::definition::object::main::NonTerminal;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::ProductionRule>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::ProductionRule;
		using type = type::definition::object::main::ProductionRule;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::ObjectPrecedence>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::ObjectPrecedence;
		using type = type::definition::object::main::ObjectPrecedence;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::ObjectAssociativity>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::ObjectAssociativity;
		using type = type::definition::object::main::ObjectAssociativity;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::Generate>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Generate;
		using type = type::definition::object::main::Generate;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::GenerateArgument>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::GenerateArgument;
		using type = type::definition::object::main::GenerateArgument;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::Integrate>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Integrate;
		using type = type::definition::object::main::Integrate;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::Name>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Name;
		using type = type::definition::object::main::Name;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::Base>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Base;
		using type = type::definition::object::Base;
	};
}

#endif // DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTTYPETOENUM_H
