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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_GRAMMAR_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_GRAMMAR_H

#include "Deamer/Language/Generator/Definition/Property/User/Base.h"
#include "Deamer/Language/Type/Definition/Property/Main/Grammar.h"

namespace deamer::language::generator::definition::property::user
{
	/*!	\class Grammar
	 *
	 *	\brief Used to generate a Grammar definition.
	 *
	 *	\tparam LanguageDefinitionType The language the Grammar is made for.
	 */
	template<typename LanguageDefinitionType>
	class Grammar : public Base<LanguageDefinitionType, type::definition::property::main::Grammar>
	{
	private:
	public:
		Grammar(LanguageDefinitionType* language_)
			: Base<LanguageDefinitionType, type::definition::property::main::Grammar>(language_)
		{
		}

		/*! \fn Generate
		 *
		 *	\brief Generates Grammar property definition.
		 */
		void GenerateDefinition() override
		{
			const auto NonTerminals = Base<LanguageDefinitionType, type::definition::property::main::Grammar>::template GetObjects<type::definition::object::Type::NonTerminal>();
			const auto ProductionRules = Base<LanguageDefinitionType, type::definition::property::main::Grammar>::template GetObjects<type::definition::object::Type::ProductionRule>();

			this->generatedDefinition = new type::definition::property::main::Grammar(NonTerminals,
				ProductionRules);
		}
	};
}

#endif // DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_USER_MAIN_GRAMMAR_H