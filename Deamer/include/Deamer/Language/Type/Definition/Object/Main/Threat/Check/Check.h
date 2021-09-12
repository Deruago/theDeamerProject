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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_CHECK_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_CHECK_H

#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Threat.h"
#include <vector>

namespace deamer::language::reference
{
	class LanguageGenerator;
}

namespace deamer::language::type::definition::property
{
	class Definition;
}

namespace deamer::language::type::definition::object::main::threat::check
{
	/*! \class Check
	 *
	 *  \brief Base class of all threat checks.
	 */
	class Check
	{
	public:
		virtual ~Check() = default;

	public:
		[[nodiscard]] virtual std::vector<Threat*> Analyze(Language* language) = 0;
		[[nodiscard]] virtual std::vector<Threat*>
		Analyze(const reference::LanguageGenerator& language) = 0;
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_CHECK_H
