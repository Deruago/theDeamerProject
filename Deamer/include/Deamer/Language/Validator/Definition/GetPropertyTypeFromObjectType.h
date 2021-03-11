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

#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/ProductionRule.h"

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
}

#endif //DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETPROPERTYTYPEFROMOBJECTTYPE_H