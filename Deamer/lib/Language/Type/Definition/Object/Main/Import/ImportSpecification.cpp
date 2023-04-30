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

#include "Deamer/Language/Type/Definition/Object/Main/Import/ImportSpecification.h"

#include <utility>

deamer::language::type::definition::object::main::ImportSpecification::ImportSpecification(object::Base* undelyingSpecialization_, 
			object::main::ImportType importType_, 
			object::main::ImportStyleType importStyleType_)
	: Base(Type::ImportSpecification),
	undelyingSpecialization(undelyingSpecialization_),
	importType(importType_),
	importStyleType(importStyleType_)
{
	references.Add(undelyingSpecialization);

}

bool deamer::language::type::definition::object::main::ImportSpecification::operator==(const ImportSpecification& rhs) const noexcept
{
	return this == &rhs || (this->undelyingSpecialization == rhs.undelyingSpecialization && this->importType == rhs.importType && this->importStyleType == rhs.importStyleType && true);
}


deamer::language::type::definition::object::main::ImportSpecification::ImportSpecification() : ImportSpecification(nullptr, 
			object::main::ImportType::reserved_default_enum_option, 
			object::main::ImportStyleType::reserved_default_enum_option)
{
}


