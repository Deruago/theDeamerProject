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

#ifndef DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETANALYZERFROMOBJECTTYPE_H
#define DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETANALYZERFROMOBJECTTYPE_H

#include "Deamer/Language/Analyzer/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Analyzer/Main/Grammar/ProductionRule.h"
#include "Deamer/Language/Analyzer/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Type.h"

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

namespace deamer::language::validator::analyzer
{
	/*! \class GetAnalyzerFromObjectType
	 *
	 *	\brief This class is used to convert LDO type to corresponding analyzer type.
	 *
	 *	\tparam T The LDO type that we want to get the analyzer from.
	 */
	template<typename T>
	class GetAnalyzerFromObjectType
	{
	public:
		constexpr static auto value = type::definition::object::Type::Unknown;
	};

	/*!
	 *	\see GetAnalyzerFromObjectType
	 */
	template<>
	class GetAnalyzerFromObjectType<type::definition::object::main::Terminal>
	{
	public:
		constexpr static auto value = type::definition::object::Type::Terminal;
		using type = deamer::language::analyzer::main::Terminal;
	};

	/*!
	 *	\see GetAnalyzerFromObjectType
	 */
	template<>
	class GetAnalyzerFromObjectType<type::definition::object::main::NonTerminal>
	{
	public:
		constexpr static auto value = type::definition::object::Type::NonTerminal;
		using type = deamer::language::analyzer::main::NonTerminal;
	};

	/*!
	 *	\see GetAnalyzerFromObjectType
	 */
	template<>
	class GetAnalyzerFromObjectType<type::definition::object::main::ProductionRule>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ProductionRule;
		using type = deamer::language::analyzer::main::ProductionRule;
	};
}

#endif // DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETANALYZERFROMOBJECTTYPE_H
