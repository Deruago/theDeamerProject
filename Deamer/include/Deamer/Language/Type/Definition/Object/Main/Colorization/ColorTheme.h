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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_COLORTHEME_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_COLORTHEME_H

#include "ColorCombination.h"
#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Type/Memory/SafeReserve.h"
#include <string>
#include <vector>

namespace deamer::language::type::definition::object::main
{
	/*! \class ColorTheme
	 *
	 *	\brief Describes a color theme.
	 *
	 *	\details Colors groups are assigned to terminals and patterns. This class is used
	 *	to give color to those groups. Color is standard rgb format.
	 *
	 *	\note The first specified color theme is the default theme.
	 */
	class ColorTheme : public Base
	{
	private:
		friend deamer::type::SafeReserve<ColorTheme>;

	public:
		std::string ThemeName;
		std::vector<ColorCombination*> ColorCombinations;

		ColorTheme(std::string themeName_, std::vector<ColorCombination*> colorCombinations_);

		bool operator==(const ColorTheme& rhs) const;

	private:
		ColorTheme();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_COLORTHEME_H
