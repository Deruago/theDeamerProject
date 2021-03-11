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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_BASEAPI_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_BASEAPI_H

#include "Deamer/Language/Generator/Definition/Property/TemplateBaseGenerator.h"
#include "Deamer/Language/Validator/Definition/GetObjectEnumsFromPropertyType.h"

namespace deamer::language::generator::definition::property::user
{
	/*! \class BaseAPI
	 *
	 *	\brief This class contains functions special to user defined property generators.
	 *
	 *	\tparam LanguageDefinitionType The language that is generated.
	 *
	 *	\tparam PropertyType The target property definition
	 */
	template<typename LanguageDefinitionType, typename PropertyType>
	class BaseAPI : public TemplateBaseGenerator<LanguageDefinitionType, PropertyType>
	{
	public:
		/*!	\property IsDefaultGenerator
		 *
		 *	\brief Used in tmp algorithms, to check whether it is a defaultgenerator.
		 */
		static constexpr bool IsDefaultGenerator = false;
		
		BaseAPI(LanguageDefinitionType* const language_)
			: TemplateBaseGenerator<LanguageDefinitionType, PropertyType>(language_)
		{
		}
		virtual ~BaseAPI() = default;

	public:
	};
}

#endif //DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_BASEAPI_H