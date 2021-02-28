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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_BASEAPI_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_BASEAPI_H

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Language/Validator/Definition/GetObjectEnumsFromPropertyType.h"
#include "Deamer/Language/Type/Definition/Object/Type.h"
#include <map>
#include <vector>


namespace deamer::language::generator::definition::property
{
	/*! \class BaseAPI
	 *
	 *	\brief This class contains the public API, which can be overridden of the base property generator class.
	 *
	 *	\details This class can be used to refer to property generators.
	 */
	class BaseAPI
	{
	protected:
		std::map<type::definition::object::Type, std::vector<type::definition::object::Base*>> bases;
	protected:
		virtual void AddObjectToInternalStorage(const type::definition::object::Type enumValue, type::definition::object::Base* const objectPointer)
		{
			bases[enumValue].push_back(objectPointer);
		}
	public:
		BaseAPI() = default;
		virtual ~BaseAPI()
		{
			
		}

		/*!	\fn GetAllObjects
		 *
		 *	\brief Returns a vector with all the objects added to the property definition generator.
		 */
		std::vector<type::definition::object::Base*> GetAllObjects() const
		{
			std::vector<type::definition::object::Base*> allObjects;
			for (const auto element : bases)
			{
				for (auto* object : element.second)
				{
					allObjects.push_back(object);
				}
			}

			return allObjects;
		}
	public:
		/*! \fn Generate
		 *
		 *	\brief This will generate a property definition.
		 *
		 *	\details This function can be overridden to allow specialized generation instructions.
		 */
		[[nodiscard]] virtual type::definition::property::Definition* Generate() = 0;
		virtual void RegisterResultToLanguageDefinition() = 0;
	};
}

#endif //DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_BASEAPI_H