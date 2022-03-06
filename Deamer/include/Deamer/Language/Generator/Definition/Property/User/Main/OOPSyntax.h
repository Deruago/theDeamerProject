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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_OOPSYNTAX_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_OOPSYNTAX_H

#include "Deamer/Language/Generator/Definition/Property/User/Base.h"
#include "Deamer/Language/Type/Definition/Property/Main/OOPSyntax.h"

namespace deamer::language::generator::definition::property::user
{
	/*!	\class OOPSyntax
	 *
	 *	\brief Used to generate a OOPSyntax definition.
	 *
	 *	\tparam LanguageDefinitionType The language the OOPSyntax is made for.
	 */
	template<typename LanguageDefinitionType>
	class OOPSyntax : public Base<LanguageDefinitionType, type::definition::property::main::OOPSyntax>
	{
	private:
	public:
		OOPSyntax(LanguageDefinitionType* language_)
			: Base<LanguageDefinitionType, type::definition::property::main::OOPSyntax>(language_)
		{
		}

		/*! \fn Generate
		 *
		 *	\brief Generates OOPSyntax property definition.
		 */
		void GenerateDefinition() override
		{
			const auto OopConceptMembers = Base<LanguageDefinitionType, type::definition::property::main::OOPSyntax>::template GetObjects<type::definition::object::Type::OopConceptMember>();
			const auto OopEncapsulations = Base<LanguageDefinitionType, type::definition::property::main::OOPSyntax>::template GetObjects<type::definition::object::Type::OopEncapsulation>();
			const auto OopLinks = Base<LanguageDefinitionType, type::definition::property::main::OOPSyntax>::template GetObjects<type::definition::object::Type::OopLink>();
			const auto OopConceptLinks = Base<LanguageDefinitionType, type::definition::property::main::OOPSyntax>::template GetObjects<type::definition::object::Type::OopConceptLink>();

			this->generatedDefinition = new type::definition::property::main::OOPSyntax(OopConceptMembers,
				OopEncapsulations,
				OopLinks,
				OopConceptLinks);
		}
	};
}

#endif // DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_OOPSYNTAX_H