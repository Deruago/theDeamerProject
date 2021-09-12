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

#include "Deamer/Language/Type/Definition/Object/Main/Colorization/TerminalColor.h"
#include "Deamer/Language/Type/Definition/Object/Main/Colorization/ColorGroup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"

deamer::language::type::definition::object::main::TerminalColor::TerminalColor(
	::deamer::language::type::definition::object::main::Terminal* terminal_, ColorGroup* colorGroup_)
	: Base(Type::TerminalColor),
	  colorGroup(colorGroup_),
	  terminal(terminal_)
{
	references.Add(terminal);
	references.Add(colorGroup);
}

bool deamer::language::type::definition::object::main::TerminalColor::operator==(
	const TerminalColor& rhs) const
{
	return this == &rhs || (this->terminal == rhs.terminal && this->colorGroup == rhs.colorGroup);
}

deamer::language::type::definition::object::main::TerminalColor::TerminalColor()
	: TerminalColor(nullptr, nullptr)
{
}
