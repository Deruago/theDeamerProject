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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_BASEAPI_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_BASEAPI_H

#include "Deamer/Language/Generator/Definition/Property/TemplateBaseGenerator.h"

namespace deamer::language::generator::definition::property::standard
{
	/*! \class BaseAPI
	 *
	 *	\brief This class contains functions special to standard defined property generators.
	 *
	 *	\tparam LanguageDefinitionType The language that is generated.
	 *
	 *	\tparam PropertyType The target property definition
	 *
	 *	\tparam Dependencies The dependencies this property generator has.
	 */
	template<typename LanguageDefinitionType, typename PropertyType, typename... Dependencies>
	class BaseAPI : public TemplateBaseGenerator<LanguageDefinitionType, PropertyType, Dependencies...>
	{
	public:
		/*!	\property IsDefaultGenerator
		 *
		 *	\brief Used in tmp algorithms, to check whether it is a defaultgenerator.
		 */
		static constexpr bool IsDefaultGenerator = true;

		BaseAPI(LanguageDefinitionType* const language_)
			: TemplateBaseGenerator<LanguageDefinitionType, PropertyType, Dependencies...>(language_)
		{
		}
		virtual ~BaseAPI() = default;
	};
}

#endif //DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_BASEAPI_H