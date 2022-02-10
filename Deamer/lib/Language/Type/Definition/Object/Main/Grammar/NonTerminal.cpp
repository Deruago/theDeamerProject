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

#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminal.h"

#include <utility>

deamer::language::type::definition::object::main::NonTerminal::NonTerminal(std::string Name_, 
			std::vector<object::main::ProductionRule*> ProductionRules_, 
			object::main::NonTerminalAbstraction abstraction_, 
			bool Inline_)
	: Base(Type::NonTerminal),
	Name(Name_),
	ProductionRules(ProductionRules_),
	abstraction(abstraction_),
	Inline(Inline_)
{
	references.Add(ProductionRules);

}

bool deamer::language::type::definition::object::main::NonTerminal::operator==(const NonTerminal& rhs) const noexcept
{
	return this == &rhs || (this->Name == rhs.Name && this->ProductionRules == rhs.ProductionRules && this->abstraction == rhs.abstraction && this->Inline == rhs.Inline && true);
}


deamer::language::type::definition::object::main::NonTerminal::NonTerminal() : NonTerminal("", 
			std::vector<object::main::ProductionRule*>{}, 
			object::main::NonTerminalAbstraction::reserved_default_enum_option, 
			false)
{
}


bool deamer::language::type::definition::object::main::NonTerminal::IsInlined() const noexcept
{
	return Inline;
}

bool deamer::language::type::definition::object::main::NonTerminal::IsReserved() const noexcept
{
	return Name.find("deamerreserved") == 0;
}

