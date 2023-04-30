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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_VALUE_VALUEABSTRACTION_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_VALUE_VALUEABSTRACTION_H

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Language/Type/Definition/Object/Main/Value/ValueAbstractionType.h"
#include "Deamer/Language/Type/Definition/Object/Main/Value/ValueAbstraction.h"


#include "Deamer/Type/Memory/SafeReserve.h"
#include <string>
#include <vector>
#include <optional>

namespace deamer::language::type::definition::object::main
{
	/*! \class ValueAbstraction
	 *
	 *	\brief 

	 *	\details 

	 */
	class ValueAbstraction : public Base
	{
	private:
		friend deamer::type::SafeReserve<ValueAbstraction>;
	
	public:
		object::main::ValueAbstractionType abstractionType;
		std::string abstractValue;
		std::vector<object::main::ValueAbstraction*> underlyingValueAbstractions;


	public:
		ValueAbstraction(object::main::ValueAbstractionType abstractionType_, 
			std::string abstractValue_, 
			std::vector<object::main::ValueAbstraction*> underlyingValueAbstractions_);

		// Compares if two ValueAbstraction have the same value.
		//
		// This means that two identical but different LDOs are equal.
		// However, pointer equality will fail as they are not the same LDO.
		// They only have the same value.
		bool operator==(const ValueAbstraction& rhs) const noexcept;

	public:


	protected:
		ValueAbstraction();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_VALUE_VALUEABSTRACTION_H
