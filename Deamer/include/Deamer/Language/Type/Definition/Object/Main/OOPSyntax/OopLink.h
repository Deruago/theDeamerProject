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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_OOPSYNTAX_OOPLINK_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_OOPSYNTAX_OOPLINK_H

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/ProductionRule.h"
#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopConceptLink.h"


#include "Deamer/Type/Memory/SafeReserve.h"
#include <string>
#include <vector>
#include <optional>

namespace deamer::language::type::definition::object::main
{
	/*! \class OopLink
	 *
	 *	\brief 

	 *	\details 

	 */
	class OopLink : public Base
	{
	private:
		friend deamer::type::SafeReserve<OopLink>;
	
	public:
		object::main::ProductionRule* productionRule;
		std::vector<object::main::OopConceptLink*> OopConceptLinks;


	public:
		OopLink(object::main::ProductionRule* productionRule_, 
			std::vector<object::main::OopConceptLink*> OopConceptLinks_);

		// Compares if two OopLink have the same value.
		//
		// This means that two identical but different LDOs are equal.
		// However, pointer equality will fail as they are not the same LDO.
		// They only have the same value.
		bool operator==(const OopLink& rhs) const noexcept;

	public:


	protected:
		OopLink();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_OOPSYNTAX_OOPLINK_H
