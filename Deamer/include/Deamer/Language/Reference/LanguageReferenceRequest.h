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

#ifndef DEAMER_LANGUAGE_REFERENCE_LANGUAGEREFERENCEREQUEST_H
#define DEAMER_LANGUAGE_REFERENCE_LANGUAGEREFERENCEREQUEST_H

#include "Deamer/Language/Type/Definition/Property/Type.h"
#include "Deamer/Language/Reference/RequirementLevel.h"

namespace deamer::language::reference
{
	/*! \class LanguageReferenceRequest
	 *
	 *	\brief LanguageReferenceRequest is used by reference classes to request definitions.
	 *
	 *	\details LanguageReferenceRequest
	 */
	class LanguageReferenceRequest
	{
	private:
		const type::definition::property::Type Type;
		const RequirementLevel Level;
	public:
		LanguageReferenceRequest(const type::definition::property::Type type_, const RequirementLevel level = RequirementLevel::Needed) noexcept;

		type::definition::property::Type GetPropertyType() const noexcept;
		RequirementLevel GetRequirementLevel() const noexcept;
	};
}

#endif //DEAMER_LANGUAGE_REFERENCE_LANGUAGEREFERENCEREQUEST_H