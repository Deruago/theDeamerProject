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

#include "Deamer/Language/Type/Definition/Object/Main/Associativity/AssociativityType.h"
#include "Deamer/Language/Type/Definition/Object/Main/Associativity/ObjectAssociativity.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/Color.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorCombination.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorGroup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorTheme.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/TerminalColor.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/TerminalPatternColor.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminalAbstraction.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/ProductionRule.h"
#include "Deamer/Language/Type/Definition/Object/Main/Identity/Name.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/SpecialType.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Precedence/ObjectPrecedence.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat.h"

#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Threat.h"
#include "Deamer/Language/Type/Definition/Object/Type.h"

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
	class ObjectEnumToType<type::definition::object::Type::AssociativityType>
	{
	public:
		constexpr static auto value = type::definition::object::Type::AssociativityType;
		using type = type::definition::object::main::AssociativityType;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ObjectAssociativity>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ObjectAssociativity;
		using type = type::definition::object::main::ObjectAssociativity;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::Color>
	{
	public:
		constexpr static auto value = type::definition::object::Type::Color;
		using type = type::definition::object::main::Color;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ColorCombination>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ColorCombination;
		using type = type::definition::object::main::ColorCombination;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ColorGroup>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ColorGroup;
		using type = type::definition::object::main::ColorGroup;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ColorTheme>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ColorTheme;
		using type = type::definition::object::main::ColorTheme;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::TerminalColor>
	{
	public:
		constexpr static auto value = type::definition::object::Type::TerminalColor;
		using type = type::definition::object::main::TerminalColor;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::TerminalPatternColor>
	{
	public:
		constexpr static auto value = type::definition::object::Type::TerminalPatternColor;
		using type = type::definition::object::main::TerminalPatternColor;
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
	class ObjectEnumToType<type::definition::object::Type::NonTerminalAbstraction>
	{
	public:
		constexpr static auto value = type::definition::object::Type::NonTerminalAbstraction;
		using type = type::definition::object::main::NonTerminalAbstraction;
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
	class ObjectEnumToType<type::definition::object::Type::Name>
	{
	public:
		constexpr static auto value = type::definition::object::Type::Name;
		using type = type::definition::object::main::Name;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::SpecialType>
	{
	public:
		constexpr static auto value = type::definition::object::Type::SpecialType;
		using type = type::definition::object::main::SpecialType;
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
	class ObjectEnumToType<type::definition::object::Type::ObjectPrecedence>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ObjectPrecedence;
		using type = type::definition::object::main::ObjectPrecedence;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::Threat>
	{
	public:
		constexpr static auto value = type::definition::object::Type::Threat;
		using type = type::definition::object::main::threat::Threat;
	};


}

#endif // DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTENUMTOTYPE_H