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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_BASE_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_BASE_H

#include "Deamer/Language/Generator/Definition/Property/User/BaseAPI.h"
#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Language/Generator/Definition/Base.h"
#include <map>

namespace deamer::language::generator::definition::property::user
{
	/*!	\class Base
	 *
	 *	\brief The base class of all property definition generators
	 *
	 *	\details This base class contains logic to automatically handle the generation of property definitions.
	 *	It contains API's to add objects, get objects, and generate the actual definition.
	 *	All code can however be overridden allowing the user to specialize different stages.
	 *
	 *	Sub classes contain standard implementations.
	 *
	 *	\tparam LanguageDefinitionType Used to specify the language definition class used to generate a specific language.
	 *
	 *	\tparam PropertyType Used to deduce the allowed Object Types for the property definition.
	 */
	template<typename LanguageDefinitionType, typename PropertyType>
	class Base : public BaseAPI<LanguageDefinitionType, PropertyType>
	{
	public:
		Base(LanguageDefinitionType* const language_)
			: BaseAPI<LanguageDefinitionType, PropertyType>(language_)
		{
			static_assert(std::is_base_of<definition::Base, LanguageDefinitionType>::value, "Given Language definition type is not a derived class of a Language generator!");
		}
		~Base() override = default;
	};
}

#endif //DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_BASE_H