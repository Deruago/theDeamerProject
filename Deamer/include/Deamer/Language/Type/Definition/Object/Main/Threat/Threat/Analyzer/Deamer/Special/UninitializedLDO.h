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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_THREAT_ANALYZER_DEAMER_SPECIAL_UNINITIALIZEDLDO_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_THREAT_ANALYZER_DEAMER_SPECIAL_UNINITIALIZEDLDO_H

#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Analyzer/Deamer/Special/Type.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Warning.h"
#include "Deamer/Language/Type/Definition/Object/Special/Uninitialized.h"
#include "Deamer/Type/Memory/SafeReserve.h"

namespace deamer::language::type::definition::object::main::threat::deamer::special
{
	/*! \class Uninitialized
	 *
	 */
	class Uninitialized : public Warning
	{
		friend ::deamer::type::SafeReserve<Uninitialized>;

	public:
		static constexpr auto id = Type::Base;
		static constexpr auto analyzerType = analyzer::Type::Deamer_Special;

		::deamer::language::type::definition::object::special::BaseUninitialized* uninitialized;

	public:
		Uninitialized(::deamer::language::type::definition::object::special::BaseUninitialized*
						  uninitialized_);

		~Uninitialized() override = default;

		std::string Print() const override;

	protected:
		Uninitialized();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_THREAT_ANALYZER_DEAMER_SPECIAL_UNINITIALIZEDLDO_H
