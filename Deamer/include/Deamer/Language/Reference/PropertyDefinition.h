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

#include "Deamer/Language/Convertor/Definition/PropertyEnumToType.h"
#include "Deamer/Language/Exception/RequestedPropertyDefinitionNotFound.h"
#include "Deamer/Language/Type/Definition/Language.h"
#include "Deamer/Language/Type/Definition/Property/Type.h"
#include <iostream>
#include <vector>

namespace deamer::language::reference
{
	class PropertyDefinitionBase
	{
	protected:
		const type::definition::Language* const Language = nullptr;

	public:
		PropertyDefinitionBase() = default;
		PropertyDefinitionBase(const type::definition::Language* language_) : Language(language_)
		{
			if (Language == nullptr)
			{
				throw std::logic_error("language_ was null-pointer");
			}
		}

		virtual ~PropertyDefinitionBase() = default;

		virtual bool IsDefinitionRequested(
			const type::definition::property::Definition* const definition) const noexcept = 0;

		virtual const type::definition::property::Definition*
		GetBasePropertyDefinition(const type::definition::property::Type type_) const = 0;

		virtual bool IsDefinitionAvailable(type::definition::property::Type type) const = 0;

		deamer::type::memory::Cache<type::definition::object::Base, type::definition::object::Type>*
		GetLanguageCache() const
		{
			if (Language == nullptr)
			{
				throw std::logic_error("language_ was null-pointer");
			}
			return &Language->cache;
		}
	};

	/*! \class PropertyDefinition
	 *
	 *	\brief This class is used to reference a property definition in a Language definition.
	 *
	 *	\details You can request specific property definitions using the template parameters.
	 *	The ctor will then modify its referencing manner to include only the things you have
	 *requested.
	 *
	 *	\note The references are all const and can thus not be modified.
	 */
	template<const type::definition::property::Type... types>
	class PropertyDefinition : public PropertyDefinitionBase
	{
	private:
		[[nodiscard]] std::vector<const type::definition::property::Definition*>
		GetPropertyDefinitions(const type::definition::Language* language) const
		{
			std::vector<const type::definition::property::Definition*> propertyDefinitions;
			for (auto* propertyDefinition : language->propertyDefinitions)
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
		constexpr static auto requestedTypes = {
			type::definition::property::Type::Identity,
			type::definition::property::Type::Generation,
			types...,
		};
		const std::vector<const type::definition::property::Definition*> requestedDefinitions;

		PropertyDefinition(const type::definition::Language* language)
			: PropertyDefinitionBase(language),
			  requestedDefinitions(GetPropertyDefinitions(language))
		{
		}

		PropertyDefinition(const PropertyDefinition& propertyDefinition)
			: PropertyDefinitionBase(propertyDefinition.Language),
			  requestedDefinitions(propertyDefinition.requestedDefinitions)
		{
		}

		~PropertyDefinition() override = default;

		PropertyDefinition& operator=(const PropertyDefinition& propertyDefinition) = delete;
		PropertyDefinition& operator=(PropertyDefinition&& propertyDefinition) noexcept = delete;

		/*! \fn IsDefinitionRequested
		 *
		 *	\brief This function is used to check if a specific definition is requested.
		 *
		 *	\details It checks this by asking a pointer to the definition.
		 */
		bool IsDefinitionRequested(
			const type::definition::property::Definition* const definition) const noexcept override
		{
			for (auto requestedElement : requestedTypes)
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
		 *	\returns It will automatically return a downcast-ed constant reference to the requested
		 *type.
		 *
		 *	\note It will throw an exception::RequestedPropertyDefinitionNotFound whenever it cannot
		 *find the requested definition.
		 */
		template<const type::definition::property::Type type>
		const convertor::definition::PropertyEnumToType_t<type>& GetDefinition() const
		{
			using RequestedLPDPointer =
				const convertor::definition::PropertyEnumToType_t<type>* const;

			const auto* definition = GetBasePropertyDefinition(type);

			return *static_cast<RequestedLPDPointer>(definition);
		}

		const type::definition::property::Definition*
		GetBasePropertyDefinition(const type::definition::property::Type type_) const override
		{
			for (const auto* definition : requestedDefinitions)
			{
				if (definition->GetType() == type_)
				{
					return definition;
				}
			}
			throw exception::RequestedPropertyDefinitionNotFound{};
		}

		bool IsDefinitionAvailable(type::definition::property::Type type) const override
		{
			for (const auto* definition : requestedDefinitions)
			{
				if (definition->GetType() == type)
				{
					return true;
				}
			}
			return false;
		}
	};
}

#endif // DEAMER_LANGUAGE_REFERENCE_PROPERTYDEFINITION_H
