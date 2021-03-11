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

#ifndef DEAMER_LANGUAGE_REFERENCE_LANGUAGEGENERATOR_H
#define DEAMER_LANGUAGE_REFERENCE_LANGUAGEGENERATOR_H

#include "Deamer/Language/Generator/Definition/Base.h"
#include "Deamer/Language/Type/Definition/Property/Type.h"
#include "Deamer/Language/Convertor/Definition/PropertyEnumToType.h"
#include "Deamer/Language/Exception/RequestedPropertyDefinitionNotFound.h"
#include <vector>

namespace deamer::language::reference
{
	/*! \class LanguageGenerator
	 *
	 *	\brief A reference used to reference definitions and objects inside a Language Generator.
	 *
	 *	\note The references are all const and can thus not be modified.
	 */
	class LanguageGenerator
	{
	private:
		[[nodiscard]] std::vector<const type::definition::property::Definition*> GetPropertyDefinitions(const generator::definition::Base& language) const
		{
			std::vector<const type::definition::property::Definition*> propertyDefinitions;
			for (auto* propertyDefinition : language.GetDefinitions())
			{
				propertyDefinitions.push_back(propertyDefinition);
			}

			return propertyDefinitions;
		}
		const generator::definition::Base& Language;
	public:
		const std::vector<const type::definition::property::Definition*> requestedDefinitions;

		LanguageGenerator(const generator::definition::Base& languageGenerator)
			: Language(languageGenerator),
			requestedDefinitions(GetPropertyDefinitions(languageGenerator))
		{
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
			for (const auto* definition : requestedDefinitions)
			{
				if (definition->GetType() == type)
				{
					return *static_cast<const typename convertor::definition::PropertyEnumToType<type>::type*>(definition);
				}
			}
			throw exception::RequestedPropertyDefinitionNotFound{};
		}
	};
}

#endif //DEAMER_LANGUAGE_REFERENCE_LANGUAGEGENERATOR_H