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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_CHECKOUTPUT_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_CHECKOUTPUT_H

#include "Deamer/Language/Type/Definition/Object/Main/Threat/Analyzer/Type.h"
#include <cstddef>

namespace deamer::language::type::definition::object::main::threat::check
{
	struct CheckInformation
	{
		size_t id;
		::deamer::language::type::definition::object::main::threat::analyzer::Type analyzer;

		constexpr CheckInformation() : id(0), analyzer(analyzer::Type::Unknown)
		{
		}

		constexpr CheckInformation(const size_t& id_, const analyzer::Type& analyzer_)
			: id(id_),
			  analyzer(analyzer_)
		{
		}
	};

	/*! \class CheckOutput
	 *
	 *  \brief Is used to specify what threat the check outputs
	 *
	 *  \tparam T The outputted threat
	 */
	template<typename T>
	class CheckOutput
	{
	public:
		constexpr CheckOutput() = default;
		virtual ~CheckOutput() = default;

	public:
		static constexpr CheckInformation information =
			CheckInformation(static_cast<std::size_t>(T::id), T::analyzerType);
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_CHECKOUTPUT_H
