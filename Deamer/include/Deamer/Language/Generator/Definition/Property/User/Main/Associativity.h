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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_ASSOCIATIVITY_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_ASSOCIATIVITY_H

#include "Deamer/Language/Generator/Definition/Property/User/Base.h"
#include "Deamer/Language/Type/Definition/Property/Main/Associativity.h"

namespace deamer::language::generator::definition::property::user
{
	/*!	\class Associativity
	 *
	 *	\brief Used to generate a Associativity definition.
	 *
	 *	\tparam LanguageDefinitionType The language the Associativity is made for.
	 */
	template<typename LanguageDefinitionType>
	class Associativity : public Base<LanguageDefinitionType, type::definition::property::main::Associativity>
	{
	private:
	public:
		Associativity(LanguageDefinitionType* language_)
			: Base<LanguageDefinitionType, type::definition::property::main::Associativity>(language_)
		{
		}

		/*! \fn Generate
		 *
		 *	\brief Generates Associativity property definition.
		 */
		void GenerateDefinition() override
		{
			const auto AssociativityObjects = Base<LanguageDefinitionType, type::definition::property::main::Associativity>::template GetObjects<type::definition::object::Type::ObjectAssociativity>();

			this->generatedDefinition = new type::definition::property::main::Associativity(AssociativityObjects);
		}
	};
}

#endif // DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_ASSOCIATIVITY_H