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

#ifndef DEAMER_LANGUAGE_CONVERTOR_DEFINITION_PROPERTYENUMTOTYPE_H
#define DEAMER_LANGUAGE_CONVERTOR_DEFINITION_PROPERTYENUMTOTYPE_H

#include "Deamer/Language/Type/Definition/Property/Type.h"
#include "Deamer/Language/Type/Definition/Property/Main/Associativity.h"
#include "Deamer/Language/Type/Definition/Property/Main/AstOptimization.h"
#include "Deamer/Language/Type/Definition/Property/Main/AstTranslation.h"
#include "Deamer/Language/Type/Definition/Property/Main/Colorization.h"
#include "Deamer/Language/Type/Definition/Property/Main/Documentation.h"
#include "Deamer/Language/Type/Definition/Property/Main/Formatting.h"
#include "Deamer/Language/Type/Definition/Property/Main/Grammar.h"
#include "Deamer/Language/Type/Definition/Property/Main/Lexicon.h"
#include "Deamer/Language/Type/Definition/Property/Main/Precedence.h"
#include "Deamer/Language/Type/Definition/Property/Main/Semantic.h"

namespace deamer::language::convertor::definition
{
	/*! \class PropertyEnumToType
	 *
	 *	\brief This class is used to convert property enum types into typenames
	 *	
	 *	\tparam T The enum value that needs to be converted to a typename
	 *
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 */
	template<type::definition::property::Type T>
	class PropertyEnumToType
	{
	public:
		constexpr static auto value = type::definition::property::Type::Unknown;
		using type = void;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<>
	class PropertyEnumToType<type::definition::property::Type::Associativity>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Associativity;
		using type = type::definition::property::main::Associativity;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<>
	class PropertyEnumToType<type::definition::property::Type::AstOptimization>
	{
	public:
		constexpr static auto value = type::definition::property::Type::AstOptimization;
		using type = type::definition::property::main::AstOptimization;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<>
	class PropertyEnumToType<type::definition::property::Type::AstTranslation>
	{
	public:
		constexpr static auto value = type::definition::property::Type::AstTranslation;
		using type = type::definition::property::main::AstTranslation;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<>
	class PropertyEnumToType<type::definition::property::Type::Precedence>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Precedence;
		using type = type::definition::property::main::Precedence;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<>
	class PropertyEnumToType<type::definition::property::Type::Lexicon>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Lexicon;
		using type = type::definition::property::main::Lexicon;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<>
	class PropertyEnumToType<type::definition::property::Type::Grammar>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Grammar;
		using type = type::definition::property::main::Grammar;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<>
	class PropertyEnumToType<type::definition::property::Type::Semantic>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Semantic;
		using type = type::definition::property::main::Semantic;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<>
	class PropertyEnumToType<type::definition::property::Type::Colorization>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Colorization;
		using type = type::definition::property::main::Colorization;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<>
	class PropertyEnumToType<type::definition::property::Type::Formatting>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Formatting;
		using type = type::definition::property::main::Formatting;
	};

	/*!
	 *	\see deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<>
	class PropertyEnumToType<type::definition::property::Type::Documentation>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Documentation;
		using type = type::definition::property::main::Documentation;
	};
}

#endif //DEAMER_LANGUAGE_CONVERTOR_DEFINITION_PROPERTYENUMTOTYPE_H