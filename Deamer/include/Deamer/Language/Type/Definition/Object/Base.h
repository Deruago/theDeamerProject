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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_BASE_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_BASE_H

#include "Deamer/Language/Type/Definition/Object/Type.h"
#include <map>
#include <set>

namespace deamer::language::type::definition::object {
	/*! \class Base
	 *
	 *  The base class of all language definition objects.
	 */
	class Base
	{
	protected:
		/*! \property Cache
		 *
		 *	\brief This is used for reverse lookup.
		 *
		 *	\details Cache is managed using the base class. It serves as reverse lookup feature.
		 */
		std::map<Type, std::set<Base*>> Cache;

		/*! \fn Register
		 *
		 *	\brief This function can be used to register a reference.
		 *
		 *	\details Registering a reference is used in reverse lookup.
		 */
		void Register() const noexcept {}
	public:
		deamer::language::type::definition::object::Type Type_;
		
		Base(const object::Type type_);
		
		virtual ~Base() = default;
	};
}

#endif //DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_BASE_H