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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_COLORCOMBINATION_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_COLORCOMBINATION_H

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/Color.h"
#include "Deamer/Type/Memory/SafeReserve.h"
#include <string>
#include <vector>

namespace deamer::language::type::definition::object::main
{
	class ColorGroup;

	/*! \class ColorCombination
	 *
	 *	\brief Describes what color a specific group should be.
	 *
	 *	\details Used by ColorTheme to specify color.
	 */
	class ColorCombination : public Base
	{
	private:
		friend deamer::type::SafeReserve<ColorCombination>;

	public:
		ColorGroup* colorGroup;
		Color color;

		ColorCombination(ColorGroup* colorGroup_, Color color_);

		bool operator==(const ColorCombination& rhs) const;

	private:
		ColorCombination();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_COLORCOMBINATION_H
