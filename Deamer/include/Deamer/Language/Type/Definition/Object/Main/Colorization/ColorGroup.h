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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_COLORGROUP_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_COLORGROUP_H

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Type/Memory/SafeReserve.h"
#include <string>
#include <vector>

namespace deamer::language::type::definition::object::main
{
	/*! \class ColorGroup
	 *
	 *	\brief Describes a specific ColorGroup.
	 *
	 *	\details A color group is a set of terminals and patterns having the same color.
	 *	The color is however applied by the theme. This allows more versatility in defining colors.
	 *
	 *	\note The ColorGroup of value 0, is reserved.
	 *	0 indicates that the generator may fill it in for themselves.
	 *	So always use values > 0. Unless the other behaviour is preferred.
	 */
	class ColorGroup : public ::deamer::language::type::definition::object::Base
	{
	private:
		friend deamer::type::SafeReserve<ColorGroup>;

	public:
		std::size_t ColorId;

		ColorGroup();
		ColorGroup(std::size_t colorId);

		bool operator==(const ColorGroup& rhs) const;

		~ColorGroup() override = default;

	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_COLORGROUP_H
