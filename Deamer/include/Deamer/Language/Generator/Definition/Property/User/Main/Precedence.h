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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_PRECEDENCE_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_PRECEDENCE_H

#include "Deamer/Language/Generator/Definition/Property/User/Base.h"
#include "Deamer/Language/Type/Definition/Property/Main/Precedence.h"

namespace deamer::language::generator::definition::property::user
{
	/*!	\class Precedence
	 *
	 *	\brief Used to generate a Precedence definition.
	 *
	 *	\tparam LanguageDefinitionType The language the Precedence is made for.
	 */
	template<typename LanguageDefinitionType>
	class Precedence : public Base<LanguageDefinitionType, type::definition::property::main::Precedence>
	{
	private:
	public:
		Precedence(LanguageDefinitionType* language_)
			: Base<LanguageDefinitionType, type::definition::property::main::Precedence>(language_)
		{
		}

		/*! \fn Generate
		 *
		 *	\brief Generates Precedence property definition.
		 */
		void GenerateDefinition() override
		{
			const auto PrecedenceObjects = Base<LanguageDefinitionType, type::definition::property::main::Precedence>::template GetObjects<type::definition::object::Type::ObjectPrecedence>();

			this->generatedDefinition = new type::definition::property::main::Precedence(PrecedenceObjects);
		}
	};
}

#endif // DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_PRECEDENCE_H