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

#ifndef DEAMER_LANGUAGE_REFERENCE_PROPERTYDEFINITION_H
#define DEAMER_LANGUAGE_REFERENCE_PROPERTYDEFINITION_H

#include "Deamer/Language/Type/Definition/Property/Type.h"
#include "Deamer/Language/Type/Definition/Language.h"
#include "Deamer/Language/Convertor/Definition/PropertyEnumToType.h"
#include "Deamer/Language/Convertor/Definition/PropertyTypeToEnum.h"
#include "Deamer/Language/Exception/RequestedPropertyDefinitionNotFound.h"
#include <vector>

namespace deamer::language::reference
{
	/*! \class PropertyDefinition
	 *
	 *	\brief This class is used to reference a property definition in a Language definition.
	 *
	 *	\details You can request specific property definitions using the template parameters.
	 *	The ctor will then modify its referencing manner to include only the things you have requested.
	 *
	 *	\note The references are all const and can thus not be modified.
	 */
	template<const type::definition::property::Type... types>
	class PropertyDefinition
	{
	private:
		[[nodiscard]] std::vector<const type::definition::property::Definition*> GetPropertyDefinitions(const type::definition::Language& language) const
		{
			std::vector<const type::definition::property::Definition*> propertyDefinitions;
			for(auto* propertyDefinition : language.propertyDefinitions)
			{
				if (IsDefinitionRequested(propertyDefinition))
				{
					propertyDefinitions.push_back(propertyDefinition);
				}
			}

			return propertyDefinitions;
		}
	public:
		constexpr static auto totalRequestedTypes = sizeof...(types);
		constexpr static std::vector<type::definition::property::Type> requestedTypes = { types... };
		const std::vector<const type::definition::property::Definition*> requestedDefinitions;
		
		PropertyDefinition(const type::definition::Language& language)
			:	requestedDefinitions(GetPropertyDefinitions(language))
		{
		}
		/*! \fn
		 *
		 *	\brief This function is used to check if a specific definition is requested.
		 *
		 *	\details It checks this by asking a pointer to the definition.
		 */
		bool IsDefinitionRequested(const type::definition::property::Definition* const definition) const noexcept
		{
			for(auto requestedElement : requestedTypes)
			{
				if (definition->GetType() == requestedElement)
				{
					return true;
				}
			}

			return false;
		}

		/*! \fn GetDefinition
		 *
		 *	\brief Get a specific requested definition.
		 *
		 *	\details By using template parameter type, you can specify which definition you want.
		 *
		 *	\tparam type The requested property definition.
		 *
		 *	\returns It will automatically return a downcast-ed constant reference to the requested type.
		 *
		 *	\note It will throw an exception::RequestedPropertyDefinitionNotFound whenever it cannot find the requested definition.
		 */
		template<type::definition::property::Type type>
		const typename convertor::definition::PropertyEnumToType<type>::type& GetDefinition() const
		{
			for (auto* definition : requestedDefinitions)
			{
				if (definition->GetType() == type)
				{
					return *static_cast<typename convertor::definition::PropertyEnumToType<type>::type*>(definition);
				}
			}
			throw exception::RequestedPropertyDefinitionNotFound{};
		}
	};
}

#endif //DEAMER_LANGUAGE_REFERENCE_PROPERTYDEFINITION_H3