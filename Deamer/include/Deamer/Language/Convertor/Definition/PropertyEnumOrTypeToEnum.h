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

#ifndef DEAMER_LANGUAGE_CONVERTOR_DEFINITION_PROPERTYENUMORTYPETOENUM_H
#define DEAMER_LANGUAGE_CONVERTOR_DEFINITION_PROPERTYENUMORTYPETOENUM_H

#include "Deamer/Language/Convertor/Definition/PropertyEnumToType.h"
#include "Deamer/Language/Convertor/Definition/PropertyTypeToEnum.h"

namespace deamer::language::convertor::definition
{
	/*! \class PropertyEnumOrTypeToEnum
	 *
	 *	\brief This class is used to convert an enumeration or type to an enum.
	 *
	 *	\tparam T The type that needs to be converted to an enum.
	 *
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 *	deamer::language::convertor::definition::PropertyEnumToType
	 */
	template<typename T>
	class PropertyEnumOrTypeToEnum : public PropertyTypeToEnum<T>
	{
	};

	/*! \class PropertyEnumOrTypeToEnum
	 *
	 *	\brief This class is used to convert an enumeration or type to a type.
	 *
	 *	\tparam T The enumerated value that needs to be converted to a type
	 *
	 *	\see deamer::language::convertor::definition::PropertyTypeToEnum
	 *	deamer::language::convertor::definition::PropertyEnumToType
	 *	deamer::language::convertor::definition::PropertyEnumOrTypeToEnum
	 */
	template<type::definition::property::Type T>
	class PropertyEnumOrTypeToEnum : public PropertyTypeToEnum<PropertyEnumToType<T>>
	{
	};
}

#endif //DEAMER_LANGUAGE_CONVERTOR_DEFINITION_PROPERTYENUMORTYPETOENUM_H