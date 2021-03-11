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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_TEMPLATEBASEGENERATOR_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_TEMPLATEBASEGENERATOR_H

#include "Deamer/Language/Convertor/Definition/ObjectEnumToType.h"
#include "Deamer/Language/Generator/Definition/Property/BaseGenerator.h"
#include "Deamer/Language/Validator/Definition/GetObjectEnumsFromPropertyType.h"
#include "Deamer/Language/Convertor/Definition/ObjectTypeToEnum.h"
#include "Deamer/Language/Convertor/Definition/PropertyTypeToEnum.h"
#include "Deamer/Language/Reference/LanguageGenerator.h"
#include "Deamer/Type/Memory/Reserve.h"
#include "Deamer/Type/Memory/SafeReserve.h"

namespace deamer::language::generator::definition::property
{
	/*!	\class TemplateBaseGenerator
	 *
	 *	\brief In this class all base logic is kept that require templates.
	 *
	 *	\tparam LanguageDefinitionType The language that is generated.
	 *
	 *	\tparam PropertyType The target property definition
	 *
	 *	\tparam Dependencies The dependencies this property generator has.
	 *	Adding new dependencies may change the generation sequence.
	 */
	template<typename LanguageDefinitionType, typename PropertyType, typename... Dependencies>
	class TemplateBaseGenerator : public BaseGenerator
	{
	protected:
		constexpr static auto objectTypes = validator::definition::GetObjectEnumsFromPropertyType<PropertyType>::value;
	public:
		using TargetPropertyDefinition_t = PropertyType;

		LanguageDefinitionType* const Language;
	public:
		TemplateBaseGenerator(LanguageDefinitionType* const language_)
			:	Language(language_)
		{
		}
		
		~TemplateBaseGenerator() override = default;

		/*!	\fn GetLanguageReference
		 *
		 *	\brief Returns a language reference to the language generator.
		 */
		reference::LanguageGenerator GetLanguageReference() const
		{
			return reference::LanguageGenerator(*Language);
		}
	public:
		static constexpr bool GeneratorHasDependencies()
		{
			return sizeof...(Dependencies) != 0;
		}

		template<const type::definition::object::Type type>
		[[nodiscard]] constexpr static bool IsObjectUsed()
		{
			for (const auto type_ : objectTypes)
			{
				if (type_ == type)
				{
					return true;
				}
			}
			return false;
		}

		/*! \fn AddObject
		 *
		 *	\brief Add a specific object, to the internal storage.
		 */
		template <typename T>
		void AddObject(const deamer::type::SafeReserve<T>& t)
		{
			constexpr static auto enumValue = convertor::definition::ObjectTypeToEnum<T>::value;
			if (!IsObjectUsed<enumValue>())
			{
				return;
			}
			AddObjectToInternalStorage(enumValue, t.Pointer());
		}

		/*! \fn AddObject
		 *
		 *	\brief Add a specific object, to the internal storage.
		 */
		template <typename T>
		void AddObject(const deamer::type::Reserve<T>& t)
		{
			constexpr static auto enumValue = convertor::definition::ObjectTypeToEnum<T>::value;
			if (!IsObjectUsed<enumValue>())
			{
				return;
			}
			AddObjectToInternalStorage(enumValue, t.Pointer());
		}

		/*! \fn AddObject
		 *
		 *	\brief Add a specific object, to the internal storage.
		 */
		template <typename T>
		void AddObject(T* const t)
		{
			constexpr static auto enumValue = convertor::definition::ObjectTypeToEnum<T>::value;
			if (!IsObjectUsed<enumValue>())
			{
				return;
			}
			AddObjectToInternalStorage(enumValue, t);
		}

		/*! \fn GetObjects
		 *
		 *	\brief Get the objects of a specific type.
		 *
		 *	\details Goes through the object map, and returns the vector with pointer to each given object.
		 */
		template<type::definition::object::Type object>
		std::vector<convertor::definition::ObjectEnumToType_t<object>*> GetObjects()
		{
			using ObjectType = convertor::definition::ObjectEnumToType_t<object>*;
			if (!IsObjectUsed<object>())
			{
				return {};
			}

			std::vector<type::definition::object::Base*> a = bases[object];
			std::vector<ObjectType> newObjectVector;
			for (auto* objectPointer : a)
			{
				newObjectVector.push_back(static_cast<ObjectType>(objectPointer));
			}

			return newObjectVector;
		}

		/*!	\fn TargetedPropertyDefinition
		 *
		 *	\brief Returns the generated property definition.
		 */
		type::definition::property::Type TargetedPropertyDefinition() const override
		{
			return convertor::definition::PropertyTypeToEnum<PropertyType>::value;
		}
		
		/*!	\fn RegisterResultToLanguageDefinition
		 *
		 *	\brief Registers the generated property definition to the language generator.
		 */
		void RegisterResultToLanguageDefinition() override
		{
			Language->RegisterDefinition(this);
		}
	};
}

#endif //DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_TEMPLATEBASEGENERATOR_H