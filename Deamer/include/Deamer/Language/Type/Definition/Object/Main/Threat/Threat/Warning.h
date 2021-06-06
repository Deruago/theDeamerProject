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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_WARNING_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_WARNING_H

#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Threat.h"
#include "Deamer/Type/Memory/SafeReserve.h"
#include <cstddef>
#include <type_traits>

namespace deamer::language::type::definition::object::main::threat
{
	/*! \class Warning
	 *
	 *  \brief A Warning LDO specifies an warning thread.
	 */
	class Warning : public Threat
	{
		friend ::deamer::type::SafeReserve<Warning>;

	public:
		Warning(const analyzer::Type analyzerType, const std::size_t id);

		template<typename T, std::enable_if_t<std::is_enum_v<T>, bool> = true>
		Warning(const analyzer::Type analyzerType, T id)
			: Warning(analyzerType, static_cast<unsigned>(id))
		{
		}

		~Warning() = default;

	protected:
		Warning();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_WARNING_H
