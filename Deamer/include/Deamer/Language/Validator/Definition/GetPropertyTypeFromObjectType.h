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
	enum class AssociativityType;
}

namespace deamer::language::type::definition::object::main
{
	class ObjectAssociativity;
}

namespace deamer::language::type::definition::object::main
{
	class Color;
}

namespace deamer::language::type::definition::object::main
{
	class ColorCombination;
}

namespace deamer::language::type::definition::object::main
{
	class ColorGroup;
}

namespace deamer::language::type::definition::object::main
{
	class ColorTheme;
}

namespace deamer::language::type::definition::object::main
{
	class TerminalColor;
}

namespace deamer::language::type::definition::object::main
{
	class TerminalPatternColor;
}

namespace deamer::language::type::definition::object::main
{
	class Generate;
}

namespace deamer::language::type::definition::object::main
{
	class GenerateArgument;
}

namespace deamer::language::type::definition::object::main
{
	class Integrate;
}

namespace deamer::language::type::definition::object::main
{
	class OSTarget;
}

namespace deamer::language::type::definition::object::main
{
	class NonTerminal;
}

namespace deamer::language::type::definition::object::main
{
	enum class NonTerminalAbstraction;
}

namespace deamer::language::type::definition::object::main
{
	class ProductionRule;
}

namespace deamer::language::type::definition::object::main
{
	class Name;
}

namespace deamer::language::type::definition::object::main
{
	enum class SpecialType;
}

namespace deamer::language::type::definition::object::main
{
	class Terminal;
}

namespace deamer::language::type::definition::object::main
{
	class OopConceptLink;
}

namespace deamer::language::type::definition::object::main
{
	class OopConceptMember;
}

namespace deamer::language::type::definition::object::main
{
	enum class OopConceptMemberType;
}

namespace deamer::language::type::definition::object::main
{
	class OopEncapsulation;
}

namespace deamer::language::type::definition::object::main
{
	class OopLink;
}

namespace deamer::language::type::definition::object::main
{
	enum class OopSyntaxScope;
}

namespace deamer::language::type::definition::object::main
{
	class ObjectPrecedence;
}

namespace deamer::language::type::definition::object::main::threat
{
	class Threat;
}



namespace deamer::language::type::definition::property::main
{
	class Associativity;
}

namespace deamer::language::type::definition::property::main
{
	class AstOptimization;
}

namespace deamer::language::type::definition::property::main
{
	class AstTranslation;
}

namespace deamer::language::type::definition::property::main
{
	class Colorization;
}

namespace deamer::language::type::definition::property::main
{
	class Documentation;
}

namespace deamer::language::type::definition::property::main
{
	class Formatting;
}

namespace deamer::language::type::definition::property::main
{
	class Generation;
}

namespace deamer::language::type::definition::property::main
{
	class Grammar;
}

namespace deamer::language::type::definition::property::main
{
	class Identity;
}

namespace deamer::language::type::definition::property::main
{
	class Lexicon;
}

namespace deamer::language::type::definition::property::main
{
	class OOPSyntax;
}

namespace deamer::language::type::definition::property::main
{
	class Precedence;
}

namespace deamer::language::type::definition::property::main
{
	class Semantic;
}

namespace deamer::language::type::definition::property::main::threat
{
	class Threat;
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
	class GetPropertyTypeFromObjectType<type::definition::object::main::AssociativityType>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Associativity;
		using type = type::definition::property::main::Associativity;
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
	class GetPropertyTypeFromObjectType<type::definition::object::main::Color>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Colorization;
		using type = type::definition::property::main::Colorization;
	};


	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::ColorCombination>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Colorization;
		using type = type::definition::property::main::Colorization;
	};


	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::ColorGroup>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Colorization;
		using type = type::definition::property::main::Colorization;
	};


	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::ColorTheme>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Colorization;
		using type = type::definition::property::main::Colorization;
	};


	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::TerminalColor>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Colorization;
		using type = type::definition::property::main::Colorization;
	};


	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::TerminalPatternColor>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Colorization;
		using type = type::definition::property::main::Colorization;
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
	class GetPropertyTypeFromObjectType<type::definition::object::main::NonTerminalAbstraction>
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
	class GetPropertyTypeFromObjectType<type::definition::object::main::Name>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Identity;
		using type = type::definition::property::main::Identity;
	};


	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::SpecialType>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Lexicon;
		using type = type::definition::property::main::Lexicon;
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
	class GetPropertyTypeFromObjectType<type::definition::object::main::OopConceptLink>
	{
	public:
		constexpr static auto value = type::definition::property::Type::OOPSyntax;
		using type = type::definition::property::main::OOPSyntax;
	};


	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::OopConceptMember>
	{
	public:
		constexpr static auto value = type::definition::property::Type::OOPSyntax;
		using type = type::definition::property::main::OOPSyntax;
	};


	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::OopConceptMemberType>
	{
	public:
		constexpr static auto value = type::definition::property::Type::OOPSyntax;
		using type = type::definition::property::main::OOPSyntax;
	};


	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::OopEncapsulation>
	{
	public:
		constexpr static auto value = type::definition::property::Type::OOPSyntax;
		using type = type::definition::property::main::OOPSyntax;
	};


	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::OopLink>
	{
	public:
		constexpr static auto value = type::definition::property::Type::OOPSyntax;
		using type = type::definition::property::main::OOPSyntax;
	};


	/*!
	 *	\see GetPropertyTypeFromObjectType
	 */
	template<>
	class GetPropertyTypeFromObjectType<type::definition::object::main::OopSyntaxScope>
	{
	public:
		constexpr static auto value = type::definition::property::Type::OOPSyntax;
		using type = type::definition::property::main::OOPSyntax;
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
	class GetPropertyTypeFromObjectType<type::definition::object::main::threat::Threat>
	{
	public:
		constexpr static auto value = type::definition::property::Type::Threat;
		using type = type::definition::property::main::Threat;
	};


}

#endif // DEAMER_LANGUAGE_VALIDATOR_DEFINITION_GETPROPERTYTYPEFROMOBJECTTYPE_H
