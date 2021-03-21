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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_SPECIAL_GENERATION_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_SPECIAL_GENERATION_H

#include "Deamer/Language/Generator/Definition/Property/User/Base.h"
#include "Deamer/Language/Type/Definition/Property/Main/Generation.h"

namespace deamer::language::generator::definition::property::user
{
	/*!	\class Generation
	 *
	 *	\brief Used to generate a identity definition.
	 *
	 *	\tparam LanguageDefinitionType The language the identity is made for.
	 */
	template<typename LanguageDefinitionType>
	class Generation
		: public Base<LanguageDefinitionType, type::definition::property::main::Generation>
	{
	private:
	public:
		Generation(LanguageDefinitionType* language_)
			: Base<LanguageDefinitionType, type::definition::property::main::Generation>(language_)
		{
		}

		/*!	\fn Generate
		 *
		 *	\brief Generates a Identity property definition.
		 *
		 */
		void GenerateDefinition() override
		{
			const auto generateStatements =
				Base<LanguageDefinitionType, type::definition::property::main::Generation>::
					template GetObjects<type::definition::object::Type::Generate>();

			const auto generateArguments =
				Base<LanguageDefinitionType, type::definition::property::main::Generation>::
					template GetObjects<type::definition::object::Type::GenerateArgument>();

			const auto integrationStatements =
				Base<LanguageDefinitionType, type::definition::property::main::Generation>::
					template GetObjects<type::definition::object::Type::Integrate>();

			this->generatedDefinition = new type::definition::property::main::Generation(
				generateStatements, generateArguments, integrationStatements);
		}
	};
}

#endif // DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_SPECIAL_GENERATION_H
