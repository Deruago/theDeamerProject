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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_GENERATION_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_GENERATION_H

#include "Deamer/Language/Type/Definition/Object/Main/Generation/Generate.h"
#include "Deamer/Language/Type/Definition/Object/Main/Generation/GeneratorArgument.h"
#include "Deamer/Language/Type/Definition/Object/Main/Generation/Integrate.h"
#include "Deamer/Language/Type/Definition/Property/Main/Definition.h"
#include <vector>

namespace deamer::language::type::definition::property::main
{
	/*! \class Generation
	 *
	 *  \brief This language property definition, defines how to generate the language.
	 *
	 *  \details This LPD is part of a set of "special" LPD's, these LPD's are always available.
	 *  Generation contains several data about what should be generated, from default tools to other
	 * ecosystem data.
	 */
	class Generation final : public Definition
	{
	public:
		// std::vector<object::main::Stages*> stages;

		std::vector<object::main::Generate*> generateStatements;
		std::vector<object::main::GenerateArgument*> generateArguments;
		std::vector<object::main::Integrate*> integrateStatements;

	public:
		Generation(std::vector<object::main::Generate*> generateStatements_,
				   std::vector<object::main::GenerateArgument*> generateArguments_,
				   std::vector<object::main::Integrate*> integrateStatements_);

		~Generation() = default;

	public:
		bool IsIntegrationSet(const object::main::Integrate& integrate) const;
		bool IsArgumentSet(const object::main::GenerateArgument& generateArgument) const;
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_GENERATION_H
