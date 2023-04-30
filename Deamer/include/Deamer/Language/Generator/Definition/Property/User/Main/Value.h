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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_VALUE_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_VALUE_H

#include "Deamer/Language/Generator/Definition/Property/User/Base.h"
#include "Deamer/Language/Type/Definition/Property/Main/Value.h"

namespace deamer::language::generator::definition::property::user
{
	/*!	\class Value
	 *
	 *	\brief Used to generate a Value definition.
	 *
	 *	\tparam LanguageDefinitionType The language the Value is made for.
	 */
	template<typename LanguageDefinitionType>
	class Value : public Base<LanguageDefinitionType, type::definition::property::main::Value>
	{
	private:
	public:
		Value(LanguageDefinitionType* language_)
			: Base<LanguageDefinitionType, type::definition::property::main::Value>(language_)
		{
		}

		/*! \fn Generate
		 *
		 *	\brief Generates Value property definition.
		 */
		void GenerateDefinition() override
		{
			const auto valueObjects = Base<LanguageDefinitionType, type::definition::property::main::Value>::template GetObjects<type::definition::object::Type::ValueObject>();
			const auto valueAbstractions = Base<LanguageDefinitionType, type::definition::property::main::Value>::template GetObjects<type::definition::object::Type::ValueAbstraction>();

			this->generatedDefinition = new type::definition::property::main::Value(valueObjects,
				valueAbstractions);
		}
	};
}

#endif // DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_VALUE_H