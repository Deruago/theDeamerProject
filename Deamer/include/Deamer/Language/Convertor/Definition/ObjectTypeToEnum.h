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

#ifndef DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTTYPETOENUM_H
#define DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTTYPETOENUM_H

#include "Deamer/Language/Type/Definition/Object/Type.h"

namespace deamer::language::type::definition::object
{
	class Base;
}


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
	class ObjectPrecedence;
}

namespace deamer::language::type::definition::object::main::threat
{
	class Threat;
}


namespace deamer::language::convertor::definition
{
	/*! \class ObjectTypeToEnum
	 *
	 *	\brief This class is used to convert object types into enumerated values.
	 *
	 *	\tparam T The type that needs to be converted to a enumerated value.
	 *
	 *	\see deamer::language::convertor::definition::ObjectEnumToType
	 */
	template<typename T>
	class ObjectTypeToEnum
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Unknown;
		using type = void;
	};

	template<typename T>
	class ObjectTypeToEnum<const T> : public ObjectTypeToEnum<T>
	{
	};

	template<typename T>
	class ObjectTypeToEnum<volatile T> : public ObjectTypeToEnum<T>
	{
	};

	template<typename T>
	class ObjectTypeToEnum<const volatile T> : public ObjectTypeToEnum<T>
	{
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::AssociativityType>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::AssociativityType;
		using type = type::definition::object::main::AssociativityType;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::ObjectAssociativity>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::ObjectAssociativity;
		using type = type::definition::object::main::ObjectAssociativity;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::Color>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Color;
		using type = type::definition::object::main::Color;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::ColorCombination>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::ColorCombination;
		using type = type::definition::object::main::ColorCombination;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::ColorGroup>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::ColorGroup;
		using type = type::definition::object::main::ColorGroup;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::ColorTheme>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::ColorTheme;
		using type = type::definition::object::main::ColorTheme;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::TerminalColor>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::TerminalColor;
		using type = type::definition::object::main::TerminalColor;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::TerminalPatternColor>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::TerminalPatternColor;
		using type = type::definition::object::main::TerminalPatternColor;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::Generate>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Generate;
		using type = type::definition::object::main::Generate;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::GenerateArgument>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::GenerateArgument;
		using type = type::definition::object::main::GenerateArgument;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::Integrate>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Integrate;
		using type = type::definition::object::main::Integrate;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::OSTarget>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::OSTarget;
		using type = type::definition::object::main::OSTarget;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::NonTerminal>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::NonTerminal;
		using type = type::definition::object::main::NonTerminal;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::NonTerminalAbstraction>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::NonTerminalAbstraction;
		using type = type::definition::object::main::NonTerminalAbstraction;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::ProductionRule>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::ProductionRule;
		using type = type::definition::object::main::ProductionRule;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::Name>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Name;
		using type = type::definition::object::main::Name;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::SpecialType>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::SpecialType;
		using type = type::definition::object::main::SpecialType;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::Terminal>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Terminal;
		using type = type::definition::object::main::Terminal;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::ObjectPrecedence>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::ObjectPrecedence;
		using type = type::definition::object::main::ObjectPrecedence;
	};


	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::main::threat::Threat>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Threat;
		using type = type::definition::object::main::threat::Threat;
	};



	/*!
	 *	\see deamer::language::convertor::definition::ObjectTypeToEnum
	 */
	template<>
	class ObjectTypeToEnum<type::definition::object::Base>
	{
	public:
		constexpr static type::definition::object::Type value =
			type::definition::object::Type::Base;
		using type = type::definition::object::Base;
	};

	template<typename T>
	using ObjectTypeToEnum_t = typename ObjectTypeToEnum<T>::type;
}

#endif // DEAMER_LANGUAGE_CONVERTOR_DEFINITION_OBJECTTYPETOENUM_H
