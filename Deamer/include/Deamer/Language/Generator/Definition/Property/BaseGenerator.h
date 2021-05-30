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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_BASEGENERATOR_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_BASEGENERATOR_H

#include "Deamer/Language/Convertor/Definition/ObjectTypeToEnum.h"
#include "Deamer/Language/Type/Definition/Property/Definition.h"
#include <map>
#include <vector>

namespace deamer::language::generator::definition::property
{
	/*!	\class BaseGenerator
	 *
	 *	\brief The base class of all property generators.
	 *
	 *	\details This class contains logic, and pure virtual functions.
	 *	It also contains the API for generating the property definition, that one can override.
	 */
	class BaseGenerator
	{
	protected:
		std::map<type::definition::object::Type, std::vector<type::definition::object::Base*>>
			bases;
		type::definition::property::Definition* generatedDefinition = nullptr;

	protected:
		/*!	\fn AddObjectToInternalStorage
		 *
		 *	\brief Adds a object to the internal storage.
		 */
		virtual void AddObjectToInternalStorage(const type::definition::object::Type enumValue,
												type::definition::object::Base* const objectPointer)
		{
			bases[enumValue].push_back(objectPointer);
		}

	public:
		BaseGenerator() = default;
		virtual ~BaseGenerator() = default;

	public:
		/*!	\fn RegisterResultToLanguageDefinition
		 *
		 *	\brief Used to register the generated property definition.
		 */
		virtual void RegisterResultToLanguageDefinition() = 0;

		/*!	\fn GenerateObjects
		 *
		 *	\brief This function will generate all objects.
		 *
		 *	\note This should be used whenever the initialization order is not correct.
		 *	e.g. First initializing a grammar LPD and then a lexicon LPD will result in nullptr references to lexicon.
		 *
		 *	The usage of an separate function solves this.
		 */
		virtual void GenerateObjects()
		{
		}

		/*!	\fn GetAllObjects
		 *
		 *	\brief Returns a vector with all the objects added to the property definition generator.
		 */
		std::vector<type::definition::object::Base*> GetAllObjects() const
		{
			std::vector<type::definition::object::Base*> allObjects;
			for (const auto& element : bases)
			{
				for (auto* object : element.second)
				{
					allObjects.push_back(object);
				}
			}

			return allObjects;
		}

		/*!	\fn CacheObjects
		 *
		 *	\brief This function is used to cache objects. To add reverse lookup capabilities.
		 */
		virtual void CacheObjects()
		{
		}

		/*! \fn Generate
		 *
		 *	\brief This will generate a property definition.
		 *
		 *	\details This function can be overridden to allow specialized generation instructions.
		 */
		virtual void GenerateDefinition() = 0;
		[[nodiscard]] virtual type::definition::property::Definition* GetDefinition() const
		{
			return generatedDefinition;
		}

		/*!	\fn ThreatAnalyzeDefinition
		 *
		 *	\brief This function is called to threat-analyze the generated definition.
		 */
		virtual void ThreatAnalyzeDefinition()
		{
		}

		/*!	\fn OptimizeDefinition
		 *
		 *	\brief This function is called to optimize the generated definition.
		 */
		virtual void OptimizeDefinition()
		{
		}

	public:
		/*!	\fn TargetedPropertyDefinition
		 *
		 *	\brief Returns the generated property definition.
		 */
		virtual type::definition::property::Type TargetedPropertyDefinition() const
		{
			return type::definition::property::Type::Unknown;
		}
	};
}

#endif // DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_BASEGENERATOR_H
