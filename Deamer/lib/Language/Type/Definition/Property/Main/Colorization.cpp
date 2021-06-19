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

#include "Deamer/Language/Type/Definition/Property/Main/Colorization.h"
#include <stdexcept>
#include <utility>

deamer::language::type::definition::property::main::Colorization::Colorization(
	std::vector<object::main::ColorGroup*> ColorGroups_,
	std::vector<object::main::ColorCombination*> ColorCombinations_,
	std::vector<object::main::ColorTheme*> ColorThemes_,
	std::vector<object::main::TerminalColor*> TerminalColors_,
	std::vector<object::main::TerminalPatternColor*> TerminalPatternColors_)
	: Definition(Type::Colorization),
	  ColorGroups(std::move(ColorGroups_)),
	  ColorCombinations(std::move(ColorCombinations_)),
	  ColorThemes(std::move(ColorThemes_)),
	  TerminalColors(std::move(TerminalColors_)),
	  TerminalPatternColors(std::move(TerminalPatternColors_))
{
	references.Add(ColorGroups);
	references.Add(ColorCombinations);
	references.Add(ColorThemes);
	references.Add(TerminalColors);
	references.Add(TerminalPatternColors);
}

deamer::language::type::definition::object::main::ColorTheme*
deamer::language::type::definition::property::main::Colorization::GetDefaultTheme() const
{
	if (ColorThemes.empty())
	{
		throw std::logic_error("There is no ColorTheme!");
	}

	return ColorThemes[0];
}
