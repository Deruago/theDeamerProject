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

#ifndef DEAMER_LANGUAGE_VALIDATOR_DEFINITION_DOESOBJECTBELONGTOPROPERTY_H
#define DEAMER_LANGUAGE_VALIDATOR_DEFINITION_DOESOBJECTBELONGTOPROPERTY_H

#include "Deamer/Language/Convertor/Definition/ObjectTypeToEnum.h"
#include "Deamer/Language/Validator/Definition/GetPropertyTypeFromObjectType.h"
#include <type_traits>

namespace deamer::language::validator::definition
{
	/*! \class DoesObjectBelongToProperty
	 *
	 *	\brief This class is used to check if type object belongs to type property.
	 *
	 *	\tparam T The LDO object
	 *
	 *	\tparam Q The property object
	 *
	 *	\see deamer::language::validator::definition::GetObjectTypesFromPropertyType
	 *	\see deamer::language::validator::definition::GetPropertyTypeFromObjectType
	 */
	template<typename T, typename Q>
	class DoesObjectBelongToProperty
	{
	private:
		constexpr static auto T_integralConstant =
			std::integral_constant<T, convertor::definition::ObjectTypeToEnum<T>::value>{};
		constexpr static auto Q_integralConstant = std::integral_constant<
			typename GetPropertyTypeFromObjectType<Q>::type,
			convertor::definition::ObjectTypeToEnum<GetPropertyTypeFromObjectType<Q>>::value>{};

	public:
		constexpr static auto value = T_integralConstant == Q_integralConstant;
		using type = void;
	};
}

#endif // DEAMER_LANGUAGE_VALIDATOR_DEFINITION_DOESOBJECTBELONGTOPROPERTY_H
