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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_BASE_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_BASE_H

#include "Deamer/Language/Type/Definition/Property/Definition.h"
#include "Deamer/Language/Type/Definition/Property/Type.h"
#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Language/Generator/Definition/Property/BaseGenerator.h"
#include <map>
#include <vector>

namespace deamer::language::generator::definition
{
	class Base
	{
	private:
		std::map<type::definition::property::Type, type::definition::property::Definition*> definitions;
		std::map<type::definition::property::Type, std::vector<type::definition::object::Base*>> objects;

	public:
		std::vector<type::definition::property::Definition*> GetDefinitions() const
		{
			std::vector<type::definition::property::Definition*> allDefinitions;
			for (const auto& element : definitions)
			{
				auto* definition = element.second;
				allDefinitions.push_back(definition);
			}

			return allDefinitions;
		}

		std::vector<type::definition::object::Base*> GetObjects() const
		{
			std::vector<type::definition::object::Base*> allObjects;
			for (const auto& element : objects)
			{
				for (auto* object : element.second)
				{
					allObjects.push_back(object);
				}
			}

			return allObjects;
		}
	public:
		Base() = default;
		virtual ~Base() = default;
	public:
		bool DefinitionAlreadyHasADefinition(type::definition::property::Type type)
		{
			return definitions[type] != nullptr;
		}

		virtual void ReplaceDefinition(type::definition::property::Type type, type::definition::property::Definition* const definition)
		{
			delete definitions[type];

			definitions[type] = definition;
		}

		virtual void ReplaceObjects(type::definition::property::Type type, const std::vector<type::definition::object::Base*>& newObjects)
		{
			objects[type] = newObjects;
		}

		virtual void RegisterDefinition(const std::vector<type::definition::object::Base*>& newObjects, type::definition::property::Definition* const newDefinition)
		{
			const type::definition::property::Type type = newDefinition->GetType();
			if (DefinitionAlreadyHasADefinition(type))
			{

				ReplaceDefinition(type, newDefinition);
				ReplaceObjects(type, newObjects);
			}

			definitions[type] = newDefinition;
			objects[type] = newObjects;
		}

		/*!	\fn RegisterDefinition
		 *
		 *	\brief Registers given propertyGenerator
		 */
		virtual void RegisterDefinition(property::BaseGenerator* propertyGenerator)
		{
			propertyGenerator->GenerateObjects();
			const auto allObjects = propertyGenerator->GetAllObjects();

			propertyGenerator->GenerateDefinition();
			auto* definition = propertyGenerator->GetDefinition();
			RegisterDefinition(allObjects, definition);
		}
	};
}

#endif //DEAMER_LANGUAGE_GENERATOR_DEFINITION_BASE_H