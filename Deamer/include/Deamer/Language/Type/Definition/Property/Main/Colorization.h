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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_COLORIZATION_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_COLORIZATION_H

#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorGroup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorCombination.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorTheme.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/TerminalColor.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/TerminalPatternColor.h"

#include "Deamer/Language/Type/Definition/Property/Main/Definition.h"
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace deamer::language::type::definition::property::main
{
	/*! \class Colorization
	 *
	 *	\brief 
	 *	Language Property Definition of the colorization, used to define the colorization for language x.
	 *	Designed by Thimo Böhmer

	 *	\details 

	 */
	class Colorization final : public Definition
	{
	public:
		std::vector<object::main::ColorGroup*> ColorGroups;
		std::vector<object::main::ColorCombination*> ColorCombinations;
		std::vector<object::main::ColorTheme*> ColorThemes;
		std::vector<object::main::TerminalColor*> TerminalColors;
		std::vector<object::main::TerminalPatternColor*> TerminalPatternColors;

	
	public:
		Colorization(std::vector<object::main::ColorGroup*> ColorGroups_, 
			std::vector<object::main::ColorCombination*> ColorCombinations_, 
			std::vector<object::main::ColorTheme*> ColorThemes_, 
			std::vector<object::main::TerminalColor*> TerminalColors_, 
			std::vector<object::main::TerminalPatternColor*> TerminalPatternColors_);
		virtual ~Colorization() = default;

	public:
		deamer::language::type::definition::object::main::ColorTheme* GetDefaultTheme() const
{
	if (ColorThemes.empty())
	{
		throw std::logic_error("There is no ColorTheme!");
	}

	return ColorThemes[0];
}
;


	public:
		

	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_COLORIZATION_H
