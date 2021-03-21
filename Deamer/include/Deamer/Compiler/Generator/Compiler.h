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

#ifndef DEAMER_COMPILER_GENERATOR_COMPILER_H
#define DEAMER_COMPILER_GENERATOR_COMPILER_H

#include "Deamer/Language/Type/Definition/Language.h"

namespace deamer::compiler::generator {

	/*!	\class Compiler
	 *
	 *	\brief This class is used to generate compiler.
	 *
	 *	\details This class automates the process of generating the LD.
	 *	It also offers an API to automate generation of the compiler.
	 *
	 *	\tparam LanguageGenerator The language generator giving the LD.
	 */
	template<typename LanguageGenerator>
	class Compiler
	{
	private:
		LanguageGenerator* languageGenerator;
		language::type::definition::Language* LanguageDefinition;
	public:
		/*!	\fn Compiler(LanguageGenerator* languageGenerator)
		 *
		 *	\brief Initializes Compiler class.
		 *
		 *	\note The LD gets immediately generated together with the LD generator.
		 */
		Compiler()
			:	languageGenerator(new LanguageGenerator()),
				LanguageDefinition(languageGenerator->GenerateLanguage())
		{
		}

		/*!	\fn Compiler(LanguageGenerator* languageGenerator)
		 *
		 *	\brief This overload allows the user to give in a specific language generator,
		 *	when there is no default constructor.
		 */
		Compiler(LanguageGenerator* languageGenerator)
			:	languageGenerator(languageGenerator),
				LanguageDefinition(languageGenerator->GenerateLanguage())
		{
		}

		virtual ~Compiler()
		{
			delete languageGenerator;
			delete LanguageDefinition;
		}
	public:
		virtual void Generate() = 0;

		/*!	\fn GetLanguageGeneration
		 *
		 *	\brief Returns a pointer to the language generator.
		 */
		LanguageGenerator* GetLanguageGeneration() const
		{
			return languageGenerator;
		}

		/*!	\fn GetLanguageDefinition
		 *
		 *	\brief Returns a pointer to the language definition.
		 */
		language::type::definition::Language* GetLanguageDefinition() const
		{
			return LanguageDefinition;
		}
	};
}

#endif //DEAMER_COMPILER_GENERATOR_COMPILER_H