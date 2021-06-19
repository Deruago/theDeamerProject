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

#include "Deamer/Language/Type/Definition/Object/Main/Colorization/TerminalPatternColor.h"
#include <utility>

deamer::language::type::definition::object::main::TerminalPatternColor::TerminalPatternColor(
	std::vector<TerminalColor*> StartTerminals_, std::vector<TerminalColor*> MiddleTerminals_,
	std::vector<TerminalColor*> EndTerminals_)
	: Base(Type::TerminalPatternColor),
	  StartTerminals(std::move(StartTerminals_)),
	  MiddleTerminals(std::move(MiddleTerminals_)),
	  EndTerminals(std::move(EndTerminals_))
{
	references.Add(StartTerminals);
	references.Add(MiddleTerminals);
	references.Add(EndTerminals);
}

bool deamer::language::type::definition::object::main::TerminalPatternColor::operator==(
	const TerminalPatternColor& rhs) const
{
	return this == &rhs || (this->StartTerminals == rhs.StartTerminals &&
							this->MiddleTerminals == rhs.MiddleTerminals &&
							this->EndTerminals == rhs.MiddleTerminals);
}

deamer::language::type::definition::object::main::TerminalPatternColor::TerminalPatternColor()
	: TerminalPatternColor({}, {}, {})
{
}
