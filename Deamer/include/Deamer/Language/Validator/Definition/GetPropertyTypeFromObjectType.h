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

#ifndef DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETPROPERTYTYPEFROMOBJECTTYPE_H
#define DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETPROPERTYTYPEFROMOBJECTTYPE_H

#include "Deamer/Language/Type/Definition/Property/Type.h"

namespace deamer::language::type::definition::object::main
{
	class ObjectAssociativity;
	class Generate;
	class GenerateArgument;
	class Integrate;
	class OSTarget;
	class NonTerminal;
	class ProductionRule;
	class Name;
	class Terminal;
	class ObjectPrecedence;
}

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

namespace deamer::language::validator::definition
{
	/*! \class GetPropertyTypeFromObjectType
	 *
	 *	\brief This class is used to retrieve the LPD that the LDO belongs to.
	 *
	 *	\tparam T The LDO type that we want to retrieve the LPD from.
	 *
	 *	\see deamer::language::validator::definition::GetObjectTypesFromPropertyType
	 */
	template<typename T>
	class GetPropertyTypeFromObjectType
	{
	public:
		constexpr static auto value = type::definition::property::Type::Unknown;
		using type = void;
	};

	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::Terminal>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Lexicon;
		using type = type::definition::property::main::Lexicon;
	};

	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::NonTerminal>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Grammar;
		using type = type::definition::property::main::Grammar;
	};

	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::ProductionRule>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Grammar;
		using type = type::definition::property::main::Grammar;
	};

	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::ObjectPrecedence>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Precedence;
		using type = type::definition::property::main::Precedence;
	};

	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::ObjectAssociativity>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Associativity;
		using type = type::definition::property::main::Associativity;
	};

	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::Generate>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Generation;
		using type = type::definition::property::main::Generation;
	};

	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::GenerateArgument>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Generation;
		using type = type::definition::property::main::Generation;
	};

	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::Integrate>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Generation;
		using type = type::definition::property::main::Generation;
	};

	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::OSTarget>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Generation;
		using type = type::definition::property::main::Generation;
	};

	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::Name>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Identity;
		using type = type::definition::property::main::Identity;
	};
}

#endif // DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETPROPERTYTYPEFROMOBJECTTYPE_H
