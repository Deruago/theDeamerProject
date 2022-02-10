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

#include "Deamer/Language/Type/Definition/Object/Main/Generation/Integrate.h"

#include <utility>

deamer::language::type::definition::object::main::Integrate::Integrate(deamer::tool::type::Tool SourceGenerator_, 
			deamer::tool::type::Tool TargetGenerator_)
	: Base(Type::Integrate),
	SourceGenerator(SourceGenerator_),
	TargetGenerator(TargetGenerator_)
{

}

bool deamer::language::type::definition::object::main::Integrate::operator==(const Integrate& rhs) const noexcept
{
	return this == &rhs || (this->SourceGenerator == rhs.SourceGenerator && this->TargetGenerator == rhs.TargetGenerator && true);
}


deamer::language::type::definition::object::main::Integrate::Integrate() : Integrate(deamer::tool::type::Tool{}, 
			deamer::tool::type::Tool{})
{
}


