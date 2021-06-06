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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_THREAT_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_THREAT_H

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/TypeInformation.h"
#include "Deamer/Type/Memory/SafeReserve.h"
#include <cstddef>
#include <string>

namespace deamer::language::type::definition::object::main::threat
{
	/*! \class Threat
	 *
	 *  \brief A threat is a LDO describing an possible issue given a LDO.
	 *
	 *  \details A threat describes an issue revolving a set of LDO's.
	 *  An example of a frequent occurring threat is: "Unused LDO".
	 *
	 *  Due to the properties of the LD and LPD system, threats are part
	 *  of language definitions.
	 *
	 *  The threat LDO is special as most information is embedded in subclasses.
	 */
	class Threat : public Base
	{
		friend ::deamer::type::SafeReserve<Threat>;

	private:
		TypeInformation typeInformation;

	public:
		Threat(const TypeInformation typeInformation_);

		~Threat() = default;

	public:
		TypeInformation GetTypeInformation() const;

	public:
		virtual std::string Print() const;

	protected:
		Threat();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_THREAT_H
