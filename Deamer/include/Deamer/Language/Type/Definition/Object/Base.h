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
#include "Deamer/Type/Vector/LDOMultiVector.h"

namespace deamer::language::type::definition
{
	class Language;
}

namespace deamer::language::type::definition::object
{
	/*! \class Base
	 *
	 *  The base class of all language definition objects.
	 */
	class Base
	{
	private:
		// This is manually controlled by the user.
		// If the user has not initialized the LDO he is required to set this to variable to true.
		// Due to the fact uninitialized objects need to be overriden, this can only be set to true.
		bool isUninitialized = false;

	protected:
		deamer::type::vector::LDOMultiVector references;

		/*! \fn Register
		 *
		 *	\brief This function can be used to register a reference.
		 *
		 *	\details Registering a reference is used in reverse lookup.
		 */
		void Register(Language& language) const;

	public:
		deamer::language::type::definition::object::Type Type_;

		Base(const object::Type type_);
		virtual ~Base() = default;

		const deamer::type::vector::LDOMultiVector& GetReferences() const;

		bool IsInitialized() const;

		/*!	\fn SetAsUninitialized
		 *
		 *	\brief Specifies that the current object is not properly initialized.
		 *
		 *	\details Uninitialised objects are non complete initialized objects should be marked as
		 *not initialized. That can be done using this function. By default safe reserved LDO's are
		 *considered uninitialized unless overriden.
		 */
		void SetAsUninitialized();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_BASE_H
