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

#ifndef DEAMER_LANGUAGE_CONVERTOR_DEFINITION_PROPERTYTYPETOENUM_H
#define DEAMER_LANGUAGE_CONVERTOR_DEFINITION_PROPERTYTYPETOENUM_H

#include "Deamer/Language/Type/Definition/Property/Type.h"

namespace deamer::language::type::definition::property::main
{
	class Associativity;
	class AstOptimization;
	class AstTranslation;
	class Colorization;
	class Documentation;
	class Formatting;
	class Generation;
	class Grammar;
	class Identity;
	class Lexicon;
	class Precedence;
	class Semantic;
}

namespace deamer::language::convertor::definition
{
	/*! \class PropertyTypeToEnum
	 *
	 *	\brief This class is used to convert property types into their enum counterparts.
	 *
	 *	\note This class functions on compile time using constexpr.
	 *
	 *	\tparam T The type that needs to be converted to an enum value.
	 *
	 *	\see deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<typename T>
	class PropertyTypeToEnum
	{
	public:
		constexpr static auto value = type::definition::property::Type::Unknown;
		using type = T;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::Associativity>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Associativity;
		using type = type::definition::property::main::Associativity;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::AstOptimization>
	{
	public:
		constexpr static auto value = type::definition::property::Type::AstOptimization;
		using type = type::definition::property::main::AstOptimization;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::AstTranslation>
	{
	public:
		constexpr static auto value = type::definition::property::Type::AstTranslation;
		using type = type::definition::property::main::AstTranslation;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::Precedence>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Precedence;
		using type = type::definition::property::main::Precedence;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::Lexicon>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Lexicon;
		using type = type::definition::property::main::Lexicon;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::Grammar>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Grammar;
		using type = type::definition::property::main::Grammar;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::Semantic>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Semantic;
		using type = type::definition::property::main::Semantic;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::Colorization>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Colorization;
		using type = type::definition::property::main::Colorization;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::Formatting>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Formatting;
		using type = type::definition::property::main::Formatting;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::Documentation>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Documentation;
		using type = type::definition::property::main::Documentation;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::Generation>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Generation;
		using type = type::definition::property::main::Generation;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<>
	class PropertyTypeToEnum<type::definition::property::main::Identity>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Identity;
		using type = type::definition::property::main::Identity;
	};
}

#endif // DEAMER_LANGUAGE_CONVERTOR_DEFINITION_PROPERTYTYPETOENUM_H
