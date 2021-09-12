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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_TERMINALCOLOR_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_TERMINALCOLOR_H

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Type/Memory/SafeReserve.h"
#include <vector>

namespace deamer::language::type::definition::object::main
{
	class ColorGroup;

	/*! \class TerminalColor
	 *
	 *	\brief Describes a specific terminal color.
	 *
	 *	\details When a terminal is encountered this will be its default color.
	 *	Unless overriden by a higher precedence type. Higher precedence are more specialized types,
	 *	thus patterns when matched will color instead of this.
	 *
	 *	\note You don't give direct colors to via TerminalColor or TerminalPatternColor.
	 *	You specify which color group they belong to. You can then specify a default ColorTheme
	 *	giving actual color.
	 *
	 *	Default color group is 0. This is unspecified meaning generators can override this value.
	 */
	class TerminalColor : public Base
	{
	private:
		friend deamer::type::SafeReserve<TerminalColor>;

	public:
		ColorGroup* colorGroup;
		Terminal* terminal;

		TerminalColor(Terminal* terminal_, ColorGroup* colorGroup_);

		bool operator==(const TerminalColor& rhs) const;

	private:
		TerminalColor();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_COLORIZATION_TERMINALCOLOR_H
