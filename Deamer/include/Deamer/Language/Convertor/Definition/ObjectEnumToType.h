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

#include "Deamer/Language/Type/Definition/Object/Main/Associativity/ObjectAssociativity.h"
#include "Deamer/Language/Type/Definition/Object/Main/Generation/Generate.h"
#include "Deamer/Language/Type/Definition/Object/Main/Generation/GeneratorArgument.h"
#include "Deamer/Language/Type/Definition/Object/Main/Generation/Integrate.h"
#include "Deamer/Language/Type/Definition/Object/Main/Generation/OSTarget.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/ProductionRule.h"
#include "Deamer/Language/Type/Definition/Object/Main/Identity/Name.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Precendence/ObjectPrecedence.h"
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
	class ObjectEnumToType<type::definition::object::Type::Generate>
	{
	public:
		constexpr static auto value = type::definition::object::Type::Generate;
		using type = type::definition::object::main::Generate;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::GenerateArgument>
	{
	public:
		constexpr static auto value = type::definition::object::Type::GenerateArgument;
		using type = type::definition::object::main::GenerateArgument;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::Integrate>
	{
	public:
		constexpr static auto value = type::definition::object::Type::Integrate;
		using type = type::definition::object::main::Integrate;
	};

	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::OSTarget>
	{
	public:
		constexpr static auto value = type::definition::object::Type::OSTarget;
		using type = type::definition::object::main::OSTarget;
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
	class ObjectEnumToType<type::definition::object::Type::Threat>
	{
	public:
		constexpr static auto value = type::definition::object::Type::Threat;
		using type = type::definition::object::main::threat::Threat;
	};

	template<type::definition::object::Type T>
	using ObjectEnumToType_t = typename ObjectEnumToType<T>::type;
}

#endif // DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTENUMTOTYPE_H
