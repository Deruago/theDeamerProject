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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_GENERATION_GENERATEARGUMENT_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_GENERATION_GENERATEARGUMENT_H

#include "Deamer/Language/Type/Definition/Object/Base.h"

#include "Deamer/Tool/Type/Tool.h"

#include "Deamer/Type/Memory/SafeReserve.h"
#include <string>
#include <vector>
#include <optional>

namespace deamer::language::type::definition::object::main
{
	/*! \class GenerateArgument
	 *
	 *	\brief 

	 *	\details 

	 */
	class GenerateArgument : public Base
	{
	private:
		friend deamer::type::SafeReserve<GenerateArgument>;
	
	public:
		deamer::tool::type::Tool Generator;
		std::string Argument;


	public:
		GenerateArgument(deamer::tool::type::Tool Generator_, 
			std::string Argument_);

		// Compares if two GenerateArgument have the same value.
		//
		// This means that two identical but different LDOs are equal.
		// However, pointer equality will fail as they are not the same LDO.
		// They only have the same value.
		bool operator==(const GenerateArgument& rhs) const noexcept;

	public:


	protected:
		GenerateArgument();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_GENERATION_GENERATEARGUMENT_H
