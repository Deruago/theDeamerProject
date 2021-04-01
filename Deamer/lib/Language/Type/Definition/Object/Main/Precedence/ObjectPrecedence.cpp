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

#include "Deamer/Language/Type/Definition/Object/Main/Precendence/ObjectPrecedence.h"

deamer::language::type::definition::object::main::ObjectPrecedence::ObjectPrecedence(
	object::Base* const object_, const int precedence_)
	: Base(object::Type::ObjectPrecedence),
	  Object(object_),
	  Precedence(precedence_)
{
	references.Add(Object);
}

deamer::language::type::definition::object::main::ObjectPrecedence::ObjectPrecedence()
	: ObjectPrecedence(nullptr, -1)
{
}
