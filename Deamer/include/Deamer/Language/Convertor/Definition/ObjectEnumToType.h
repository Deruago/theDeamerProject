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
#include "Deamer/Language/Type/Definition/Object/Main/Comment/CommentValue.h"
#include "Deamer/Language/Type/Definition/Object/Main/Generation/Generate.h"
#include "Deamer/Language/Type/Definition/Object/Main/Generation/GenerateArgument.h"
#include "Deamer/Language/Type/Definition/Object/Main/Generation/Integrate.h"
#include "Deamer/Language/Type/Definition/Object/Main/Generation/OSTarget.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminalAbstraction.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/ProductionRule.h"
#include "Deamer/Language/Type/Definition/Object/Main/Identity/Name.h"
#include "Deamer/Language/Type/Definition/Object/Main/Import/FileImport.h"
#include "Deamer/Language/Type/Definition/Object/Main/Import/FileObjectImport.h"
#include "Deamer/Language/Type/Definition/Object/Main/Import/ImportFileTarget.h"
#include "Deamer/Language/Type/Definition/Object/Main/Import/ImportSpecification.h"
#include "Deamer/Language/Type/Definition/Object/Main/Import/ImportStyleType.h"
#include "Deamer/Language/Type/Definition/Object/Main/Import/ImportSyntacticRelation.h"
#include "Deamer/Language/Type/Definition/Object/Main/Import/ImportType.h"
#include "Deamer/Language/Type/Definition/Object/Main/Import/ObjectTarget.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/SpecialType.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopConceptLink.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopConceptMember.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopConceptMemberType.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopEncapsulation.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopLink.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopSyntaxScope.h"
#include "Deamer/Language/Type/Definition/Object/Main/Precedence/ObjectPrecedence.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat.h"
#include "Deamer/Language/Type/Definition/Object/Main/Value/ValueAbstraction.h"
#include "Deamer/Language/Type/Definition/Object/Main/Value/ValueAbstractionType.h"
#include "Deamer/Language/Type/Definition/Object/Main/Value/ValueObject.h"
#include "Deamer/Language/Type/Definition/Object/Main/Value/ValueObjectType.h"

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
	class ObjectEnumToType<type::definition::object::Type::CommentValue>
	{
	public:
		constexpr static auto value = type::definition::object::Type::CommentValue;
		using type = type::definition::object::main::CommentValue;
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
	class ObjectEnumToType<type::definition::object::Type::FileImport>
	{
	public:
		constexpr static auto value = type::definition::object::Type::FileImport;
		using type = type::definition::object::main::FileImport;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::FileObjectImport>
	{
	public:
		constexpr static auto value = type::definition::object::Type::FileObjectImport;
		using type = type::definition::object::main::FileObjectImport;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ImportFileTarget>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ImportFileTarget;
		using type = type::definition::object::main::ImportFileTarget;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ImportSpecification>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ImportSpecification;
		using type = type::definition::object::main::ImportSpecification;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ImportStyleType>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ImportStyleType;
		using type = type::definition::object::main::ImportStyleType;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ImportSyntacticRelation>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ImportSyntacticRelation;
		using type = type::definition::object::main::ImportSyntacticRelation;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ImportType>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ImportType;
		using type = type::definition::object::main::ImportType;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ObjectTarget>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ObjectTarget;
		using type = type::definition::object::main::ObjectTarget;
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
	class ObjectEnumToType<type::definition::object::Type::OopConceptLink>
	{
	public:
		constexpr static auto value = type::definition::object::Type::OopConceptLink;
		using type = type::definition::object::main::OopConceptLink;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::OopConceptMember>
	{
	public:
		constexpr static auto value = type::definition::object::Type::OopConceptMember;
		using type = type::definition::object::main::OopConceptMember;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::OopConceptMemberType>
	{
	public:
		constexpr static auto value = type::definition::object::Type::OopConceptMemberType;
		using type = type::definition::object::main::OopConceptMemberType;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::OopEncapsulation>
	{
	public:
		constexpr static auto value = type::definition::object::Type::OopEncapsulation;
		using type = type::definition::object::main::OopEncapsulation;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::OopLink>
	{
	public:
		constexpr static auto value = type::definition::object::Type::OopLink;
		using type = type::definition::object::main::OopLink;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::OopSyntaxScope>
	{
	public:
		constexpr static auto value = type::definition::object::Type::OopSyntaxScope;
		using type = type::definition::object::main::OopSyntaxScope;
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


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ValueAbstraction>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ValueAbstraction;
		using type = type::definition::object::main::ValueAbstraction;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ValueAbstractionType>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ValueAbstractionType;
		using type = type::definition::object::main::ValueAbstractionType;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ValueObject>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ValueObject;
		using type = type::definition::object::main::ValueObject;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<>
	class ObjectEnumToType<type::definition::object::Type::ValueObjectType>
	{
	public:
		constexpr static auto value = type::definition::object::Type::ValueObjectType;
		using type = type::definition::object::main::ValueObjectType;
	};



	template<type::definition::object::Type T>
	using ObjectEnumToType_t = typename ObjectEnumToType<T>::type;
}

#endif // DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTENUMTOTYPE_H