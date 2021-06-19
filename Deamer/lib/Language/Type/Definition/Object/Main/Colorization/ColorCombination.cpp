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

#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorCombination.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorGroup.h"

deamer::language::type::definition::object::main::Color::Color(int r_, int g_, int b_)
	: r(r_),
	  g(g_),
	  b(b_)
{
}

bool deamer::language::type::definition::object::main::Color::operator==(const Color& rhs) const
{
	return this == &rhs || (this->r == rhs.r && this->g == rhs.g && this->b == rhs.b);
}

deamer::language::type::definition::object::main::ColorCombination::ColorCombination(
	::deamer::language::type::definition::object::main::ColorGroup* colorGroup_, Color color_)
	: Base(Type::ColorCombination),
	  colorGroup(colorGroup_),
	  color(color_)
{
	references.Add(colorGroup);
}

bool deamer::language::type::definition::object::main::ColorCombination::operator==(
	const ColorCombination& rhs) const
{
	return this == &rhs || (this->colorGroup == rhs.colorGroup && this->color == rhs.color);
}

deamer::language::type::definition::object::main::ColorCombination::ColorCombination()
	: ColorCombination(nullptr, {})
{
}
