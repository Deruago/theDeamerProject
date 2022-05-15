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

#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopConceptMember.h"

#include <utility>

deamer::language::type::definition::object::main::OopConceptMember::OopConceptMember(object::main::OopSyntaxScope scope_, 
			object::main::OopConceptMemberType member_)
	: Base(Type::OopConceptMember),
	scope(scope_),
	member(member_)
{

}

bool deamer::language::type::definition::object::main::OopConceptMember::operator==(const OopConceptMember& rhs) const noexcept
{
	return this == &rhs || (this->scope == rhs.scope && this->member == rhs.member && true);
}


deamer::language::type::definition::object::main::OopConceptMember::OopConceptMember() : OopConceptMember(object::main::OopSyntaxScope::reserved_default_enum_option, 
			object::main::OopConceptMemberType::reserved_default_enum_option)
{
}


