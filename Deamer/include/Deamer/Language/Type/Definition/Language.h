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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_LANGUAGE_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_LANGUAGE_H

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Language/Type/Definition/Property/Definition.h"
#include "Deamer/Type/Memory/Cache.h"
#include <vector>

namespace deamer::language::type::definition
{
	/*! \class Language
	 *
	 *  \brief A language definition, it has information about language x.
	 *
	 *  \details The language definition contains language property definitions (LPD), that define
	 * the language. It further contains all the language definition objects (LDO), defined by the
	 * LPD's.
	 *
	 *  \details Language definitions are used throughout Deamer to generate compilers and
	 * ecosystems.
	 */
	class Language
	{
	private:
		/*!	\property
		 *
		 *	\brief Specifies if it is temporary or not.
		 *
		 *	\note Temporary language definitions don't destroy their content.
		 */
		bool temporary;

	public:
		/*! \property propertyDefinitions
		 * \brief propertyDefinitions contains pointers to all property definitions that define the
		 * language.
		 *
		 * \details Language has ownership of these objects.
		 */
		std::vector<property::Definition*> propertyDefinitions;

		/*! \property definitionObjects
		 * \brief definitionObjects contains pointers to all definition objects used in the property
		 * definitions.
		 *
		 * \details Language has ownership of these objects.
		 */
		std::vector<object::Base*> definitionObjects;

		/*!	\property cache
		 *
		 *	\brief Used to cache references to objects in this language.
		 */
		mutable deamer::type::memory::Cache<object::Base, object::Type> cache;

		Language(std::vector<property::Definition*> propertyDefinitions_,
				 std::vector<object::Base*> definitionObjects_, bool temporary_ = false);

		Language(const Language& language) = delete;
		Language(Language&& language) = delete;

		Language operator=(const Language& language) = delete;
		Language operator=(Language&& language) = delete;

		/*! \function ~Language
		 * \brief deletes all the objects it is owner of
		 */
		~Language();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_LANGUAGE_H
