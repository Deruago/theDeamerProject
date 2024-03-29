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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_MAIN_PRECEDENCE_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_MAIN_PRECEDENCE_H

#include "Deamer/Language/Generator/Definition/Property/Standard/Base.h"
#include "Deamer/Language/Type/Definition/Object/Main/Precedence/ObjectPrecedence.h"
#include "Deamer/Language/Type/Definition/Property/Main/Precedence.h"

namespace deamer::language::generator::definition::property::standard
{
	template<typename LanguageDefinitionType>
	class Precedence
		: public Base<LanguageDefinitionType, type::definition::property::main::Precedence,
					  type::definition::property::main::Lexicon>
	{
	public:
		Precedence(LanguageDefinitionType* language_)
			: standard::Base<LanguageDefinitionType, type::definition::property::main::Precedence,
							 type::definition::property::main::Lexicon>(language_)
		{
		}
		~Precedence() override = default;

		void GenerateObjects() override
		{
			const auto& Lexicon =
				this->GetLanguageReference()
					.template GetDefinition<type::definition::property::Type::Lexicon>();

			for (auto* terminal : Lexicon.Terminals)
			{
				auto* const newObject =
					new type::definition::object::main::ObjectPrecedence(terminal, 0);
				this->AddObject(newObject);
			}
		}

		/*!	\fn Generate
		 *
		 *	\brief Generates a default precedence property definition.
		 *
		 *	\details The default precedence definition exists of a set of precedences which are all
		 *the same (0).
		 */
		void GenerateDefinition() override
		{
			auto ObjectPrecedences =
				Base<LanguageDefinitionType, type::definition::property::main::Precedence,
					 type::definition::property::main::Lexicon>::
					template GetObjects<type::definition::object::Type::ObjectPrecedence>();
			this->generatedDefinition =
				new type::definition::property::main::Precedence(ObjectPrecedences);
		}
	};
}

#endif // DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_MAIN_PRECEDENCE_H
