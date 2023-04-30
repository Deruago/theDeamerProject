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
#include "Deamer/Language/Type/Definition/Property/Main/Argument.h"
#include "Deamer/Language/Type/Definition/Property/Main/Associativity.h"
#include "Deamer/Language/Type/Definition/Property/Main/AstOptimization.h"
#include "Deamer/Language/Type/Definition/Property/Main/AstTranslation.h"
#include "Deamer/Language/Type/Definition/Property/Main/Colorization.h"
#include "Deamer/Language/Type/Definition/Property/Main/Comment.h"
#include "Deamer/Language/Type/Definition/Property/Main/Documentation.h"
#include "Deamer/Language/Type/Definition/Property/Main/Formatting.h"
#include "Deamer/Language/Type/Definition/Property/Main/Generation.h"
#include "Deamer/Language/Type/Definition/Property/Main/Grammar.h"
#include "Deamer/Language/Type/Definition/Property/Main/Identity.h"
#include "Deamer/Language/Type/Definition/Property/Main/Import.h"
#include "Deamer/Language/Type/Definition/Property/Main/Lexicon.h"
#include "Deamer/Language/Type/Definition/Property/Main/OOPSyntax.h"
#include "Deamer/Language/Type/Definition/Property/Main/Precedence.h"
#include "Deamer/Language/Type/Definition/Property/Main/Semantic.h"
#include "Deamer/Language/Type/Definition/Property/Main/Threat.h"
#include "Deamer/Language/Type/Definition/Property/Main/Value.h"


namespace deamer::language::validator::definition
{
	template<typename T>
	class GetObjectEnumsFromPropertyType
	{
	public:
		constexpr static auto value = {type::definition::object::Type::Unknown};
		using type = void;
	};

	
template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Argument>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Unknown };
		using type = type::definition::property::main::Argument;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Associativity>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::AssociativityType,
		type::definition::object::Type::ObjectAssociativity };
		using type = type::definition::property::main::Associativity;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::AstOptimization>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Unknown };
		using type = type::definition::property::main::AstOptimization;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::AstTranslation>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Unknown };
		using type = type::definition::property::main::AstTranslation;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Colorization>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Color,
		type::definition::object::Type::ColorCombination,
		type::definition::object::Type::ColorGroup,
		type::definition::object::Type::ColorTheme,
		type::definition::object::Type::TerminalColor,
		type::definition::object::Type::TerminalPatternColor };
		using type = type::definition::property::main::Colorization;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Comment>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::CommentValue };
		using type = type::definition::property::main::Comment;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Documentation>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Unknown };
		using type = type::definition::property::main::Documentation;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Formatting>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Unknown };
		using type = type::definition::property::main::Formatting;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Generation>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Generate,
		type::definition::object::Type::GenerateArgument,
		type::definition::object::Type::Integrate,
		type::definition::object::Type::OSTarget };
		using type = type::definition::property::main::Generation;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Grammar>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::NonTerminal,
		type::definition::object::Type::NonTerminalAbstraction,
		type::definition::object::Type::ProductionRule };
		using type = type::definition::property::main::Grammar;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Identity>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Name };
		using type = type::definition::property::main::Identity;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Import>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::FileImport,
		type::definition::object::Type::FileObjectImport,
		type::definition::object::Type::ImportFileTarget,
		type::definition::object::Type::ImportSpecification,
		type::definition::object::Type::ImportStyleType,
		type::definition::object::Type::ImportSyntacticRelation,
		type::definition::object::Type::ImportType,
		type::definition::object::Type::ObjectTarget };
		using type = type::definition::property::main::Import;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Lexicon>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::SpecialType,
		type::definition::object::Type::Terminal };
		using type = type::definition::property::main::Lexicon;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::OOPSyntax>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::OopConceptLink,
		type::definition::object::Type::OopConceptMember,
		type::definition::object::Type::OopConceptMemberType,
		type::definition::object::Type::OopEncapsulation,
		type::definition::object::Type::OopLink,
		type::definition::object::Type::OopSyntaxScope };
		using type = type::definition::property::main::OOPSyntax;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Precedence>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::ObjectPrecedence };
		using type = type::definition::property::main::Precedence;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Semantic>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Unknown };
		using type = type::definition::property::main::Semantic;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Threat>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::Threat };
		using type = type::definition::property::main::Threat;
	};


template<>
	class GetObjectEnumsFromPropertyType<type::definition::property::main::Value>
	{
	public:
		constexpr static auto value = { type::definition::object::Type::ValueAbstraction,
		type::definition::object::Type::ValueAbstractionType,
		type::definition::object::Type::ValueObject,
		type::definition::object::Type::ValueObjectType };
		using type = type::definition::property::main::Value;
	};


}

#endif // DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETOBJECTENUMSFROMPROPERTYTYPE_H
