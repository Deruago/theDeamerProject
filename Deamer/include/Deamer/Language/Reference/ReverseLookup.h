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

#ifndef DEAMER_LANGUAGE_REFERENCE_REVERSELOOKUP_H
#define DEAMER_LANGUAGE_REFERENCE_REVERSELOOKUP_H

#include "Deamer/Language/Convertor/Definition/ObjectTypeToEnum.h"
#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Language/Reference/ReverseLookupResult.h"
#include "Deamer/Language/Validator/Definition/GetPropertyTypeFromObjectType.h"

namespace deamer::language::reference
{
	template<typename T_lookup>
	class ReverseLookup
	{
	private:
		deamer::type::memory::Cache<type::definition::object::Base, type::definition::object::Type>*
			languageCache = nullptr;
		const PropertyDefinitionBase* const language_reference;

		const type::definition::object::Type T_lookup_enum =
			convertor::definition::ObjectTypeToEnum<T_lookup>::value;
		const type::definition::property::Type T_propertyDefinition_enum_of_lookup =
			validator::definition::GetPropertyTypeFromObjectType<T_lookup>::value;

	public:
		ReverseLookup(const PropertyDefinitionBase* const reference_)
			: language_reference(reference_)
		{
			if (language_reference == nullptr)
			{
				throw std::logic_error("Reference was null-pointer");
			}

			languageCache = language_reference->GetLanguageCache();
		}
		~ReverseLookup() = default;

	public:
		/*!	\fn Get
		 *
		 *	\brief Reverse looks up the set of T_lookup type reference to T_source object.
		 *
		 *	\details This algorithm is capable of searching first in the primary cache,
		 *	and looking up the reference via visiting the property definition (Second storage).
		 *
		 *	After it finds the set of objects in the second storage, it adds (by default)
		 *	the object to the primary cache.
		 */
		template<typename T_source>
		ReverseLookupResult<T_lookup> Get(T_source* source) const
		{
			if (source == nullptr)
			{
				return ReverseLookupResult<T_lookup>(false, CacheLocation::None);
			}

			if (!language_reference->IsDefinitionAvailable(T_propertyDefinition_enum_of_lookup))
			{
				return ReverseLookupResult<T_lookup>(false, CacheLocation::None);
			}

			auto primaryCacheResult = GetFromPrimaryCache(source);
			if (primaryCacheResult.Success())
			{
				std::cout << "Primary cache\n";
				return primaryCacheResult;
			}

			auto directLPDResult = GetFromDirectLPD(source);
			if (directLPDResult.Success())
			{
				std::cout << "Second cache\n";
				return directLPDResult;
			}

			return ReverseLookupResult<T_lookup>(false, CacheLocation::None);
		}

		template<typename T_source>
		ReverseLookupResult<T_lookup> GetFromPrimaryCache(T_source* source) const
		{
			const auto cacheResult = languageCache->Get(source, T_lookup_enum);

			if (!cacheResult.empty())
			{
				std::vector<const T_lookup*> newCache;
				for (const auto* object : cacheResult)
				{
					newCache.push_back(static_cast<const T_lookup*>(object));
				}
				return ReverseLookupResult<T_lookup>(true, CacheLocation::Primary, newCache);
			}

			return ReverseLookupResult<T_lookup>(false, CacheLocation::None);
		}

		template<typename T_source>
		ReverseLookupResult<T_lookup> GetFromDirectLPD(T_source* source,
													   bool cacheResult = true) const
		{
			const type::definition::property::Definition* definitionWithObject;
			try
			{
				definitionWithObject = language_reference->GetBasePropertyDefinition(
					T_propertyDefinition_enum_of_lookup);
			} catch ([[maybe_unused]] exception::RequestedPropertyDefinitionNotFound& ex)
			{
				return ReverseLookupResult<T_lookup>(false, CacheLocation::None);
			}

			bool found = false;
			std::vector<const T_lookup*> foundObjects;
			for (const auto& SetOfReferences : definitionWithObject->GetObjects())
			{
				if (SetOfReferences.first != T_lookup_enum)
				{
					continue;
				}

				for (const auto* reference : SetOfReferences.second)
				{
					if (reference->GetReferences().Contains(source))
					{
						found = true;
						if (cacheResult)
							languageCache->Register(reference, T_lookup_enum, source);

						foundObjects.push_back(static_cast<const T_lookup*>(reference));
					}
				}
			}

			if (found)
			{
				return ReverseLookupResult<T_lookup>(true, CacheLocation::Secondary, foundObjects);
			}
			else
			{
				return ReverseLookupResult<T_lookup>(false, CacheLocation::None);
			}
		}

		template<typename T_source>
		ReverseLookupResult<T_lookup> GetFromDirectLPD_DontCache(T_source* source) const
		{
			return GetFromDirectLPD<T_source>(source, false);
		}
	};
}

#endif // DEAMER_LANGUAGE_REFERENCE_REVERSELOOKUP_H
