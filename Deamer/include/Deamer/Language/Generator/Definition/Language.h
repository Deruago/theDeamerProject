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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_LANGUAGE_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_LANGUAGE_H

#include "Deamer/Language/Generator/Definition/Base.h"
#include "Deamer/Language/Type/Definition/Language.h"
#include "Deamer/Language/Generator/Definition/Property/User/BaseAPI.h"
#include "Deamer/Language/Generator/Definition/Property/Standard/BaseAPI.h"
#include "Deamer/Language/Validator/Generator/IsGeneratorSequenceGeneratable.h"

namespace deamer::language::generator::definition
{
	/*!	\class Language
	 *
	 *	\brief Used to generate Language Definitions with.
	 *
	 *	\details Given a set of property generators, it automatically generates the language definition.
	 *
	 *	\tparam Derived Your language class which is a subclass of this class.
	 *
	 *	\tparam PropertyGenerators A set of PropertyGenerators used in your language.
	 */
	template<typename Derived, typename... PropertyGenerators>
	class Language : public deamer::language::generator::definition::Base
	{
	public:
		Language() = default;
		virtual ~Language() = default;
	public:

		/*!	\fn GenerateLanguage
		 *
		 *	\brief Generates a language definition.
		 */
		[[nodiscard]] virtual type::definition::Language* GenerateLanguage()
		{
			GeneratePropertyDefinitions<>::template Generate<PropertyGenerators...>(this);
			const auto allDefinitions = GetDefinitions();
			const auto allObjects = GetObjects();
			return new type::definition::Language(allDefinitions, allObjects);
		}
		
		/*!	\class GeneratePropertyDefinitions
		 *
		 *	\brief This class generates the given property generators in correct order.
		 *
		 *	\details This class can receive a set of property generators.
		 *	It will automatically resolve dependency conflicts between generators.
		 *	And automatically generate the generators.
		 *
		 *	e.g.: [grammar, default_precedence, lexicon] will be executed in the order:
		 *	[grammar, lexicon, default_precedence]
		 *
		 *	It uses 2 typename packs to do its job.
		 *
		 *	\tparam FinishedGenerators The current FinishedGenerators.
		 */
		template<typename... FinishedGenerators>
		class GeneratePropertyDefinitions
		{
		private:
			/*!	\property sequenceIsValid
			 *
			 *	\brief When called checks whether the finished generators are enough to generate the current generator.
			 *
			 *	\tparam CurrentGenerator The current generator, which one wants to check the dependencies of.
			 */
			template<typename CurrentGenerator>
			static constexpr bool sequenceIsValid = validator::generator::IsGeneratorSequenceGeneratable<FinishedGenerators..., CurrentGenerator>::value;
		public:
			/*!	\fn Generate
			 *
			 *	\brief Given a set of UnfinishedGenerators correctly call generators in order.
			 *
			 *	\details Automatically generates a set of UnfinishedGenerators.
			 *	If the generators have a dependency conflict in the way they are represented,
			 *	this function automatically resolves the conflict.
			 *
			 *	It works by checking in each iteration if the current generator can be generated.
			 *	If it can be generated, we will continue to the next generator, if not we will add it at the end of the generator pack.
			 *	We will continue this, until everything is generated.
			 *
			 *	This method allows us to automatically resolve dependency conflicts.
			 *
			 *	\tparam CurrentGenerator The generator currently checked.
			 *
			 *	\tparam UnfinishedGenerators Generators that still need to be generated.
			 */
			template<typename CurrentGenerator, typename... UnfinishedGenerators>
			static constexpr void Generate(Language* language)
			{
				if constexpr (!CurrentGenerator::IsDefaultGenerator)
				{
					FinishGenerator<CurrentGenerator>(language);
					if constexpr (sizeof...(UnfinishedGenerators) > 0)
					{
						GeneratePropertyDefinitions<FinishedGenerators..., CurrentGenerator>::template Generate<UnfinishedGenerators...>(language);
					}
				}
				else
				{
					if constexpr (sequenceIsValid<CurrentGenerator>)
					{
						FinishGenerator<CurrentGenerator>(language);
						if constexpr (sizeof...(UnfinishedGenerators) > 0)
						{
							GeneratePropertyDefinitions<FinishedGenerators..., CurrentGenerator>::template Generate<UnfinishedGenerators...>(language);
						}
					}
					else
					{
						if constexpr (sizeof...(UnfinishedGenerators) > 0)
						{
							GeneratePropertyDefinitions<FinishedGenerators...>::template Generate<UnfinishedGenerators..., CurrentGenerator>(language);
						}
					}
				}
			}

			/*!	\fn FinishGenerator
			 *
			 *	\brief Finishes a generator.
			 *
			 *	\details Finishes a generator.
			 *	It correctly calls each stage of the generator, until it is fully generated (finished).
			 *	
			 *	\tparam Generator The generator that we can finish.
			 */
			template<typename Generator>
			static void FinishGenerator(Language* language)
			{
				static_cast<Derived*>(language)->Generator::RegisterResultToLanguageDefinition();
			}
		};
	};
}

#endif //DEAMER_LANGUAGE_GENERATOR_DEFINITION_LANGUAGE_H