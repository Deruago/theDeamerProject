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

#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopEncapsulation.h"

#include <utility>

deamer::language::type::definition::object::main::OopEncapsulation::OopEncapsulation(object::main::NonTerminal* nonTerminal_, 
			object::main::OopSyntaxScope scope_)
	: Base(Type::OopEncapsulation),
	nonTerminal(nonTerminal_),
	scope(scope_)
{
	references.Add(nonTerminal);

}

bool deamer::language::type::definition::object::main::OopEncapsulation::operator==(const OopEncapsulation& rhs) const noexcept
{
	return this == &rhs || (this->nonTerminal == rhs.nonTerminal && this->scope == rhs.scope && true);
}


deamer::language::type::definition::object::main::OopEncapsulation::OopEncapsulation() : OopEncapsulation(nullptr, 
			object::main::OopSyntaxScope::reserved_default_enum_option)
{
}


