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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_OOPSYNTAX_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_OOPSYNTAX_H

#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopConceptLink.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopConceptMember.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopEncapsulation.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopLink.h"
#include "Deamer/Language/Type/Definition/Property/Main/Definition.h"
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace deamer::language::type::definition::property::main
{
	/*! \class OOPSyntax
	 *
	 *	\brief
	 *	OOPSyntax can be used to specify what parts of your language correspond
	 *	with OOP concepts.
	 *	Designed by Thimo Böhmer.

	 *	\details

	 */
	class OOPSyntax final : public Definition
	{
	public:
		std::vector<object::main::OopConceptMember*> OopConceptMembers;
		std::vector<object::main::OopEncapsulation*> OopEncapsulations;
		std::vector<object::main::OopLink*> OopLinks;
		std::vector<object::main::OopConceptLink*> OopConceptLinks;

	public:
		OOPSyntax(std::vector<object::main::OopConceptMember*> OopConceptMembers_,
				  std::vector<object::main::OopEncapsulation*> OopEncapsulations_,
				  std::vector<object::main::OopLink*> OopLinks_,
				  std::vector<object::main::OopConceptLink*> OopConceptLinks_);
		virtual ~OOPSyntax() = default;

	public:
	public:
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_OOPSYNTAX_H
