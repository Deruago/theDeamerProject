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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_ASSOCIATIVITY_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_ASSOCIATIVITY_H

#include "Deamer/Language/Type/Definition/Object/Main/Associativity/ObjectAssociativity.h"

#include "Deamer/Language/Type/Definition/Property/Main/Definition.h"
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace deamer::language::type::definition::property::main
{
	/*! \class Associativity
	 *
	 *	\brief 
	 *	Language Property Definition of the associativity,
	 *	used to define the associativity of symbols in language x.

	 *	\details 

	 */
	class Associativity final : public Definition
	{
	public:
		std::vector<object::main::ObjectAssociativity*> AssociativityObjects;

	
	public:
		Associativity(std::vector<object::main::ObjectAssociativity*> AssociativityObjects_);
		virtual ~Associativity() = default;

	public:


	public:
		

	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_ASSOCIATIVITY_H
