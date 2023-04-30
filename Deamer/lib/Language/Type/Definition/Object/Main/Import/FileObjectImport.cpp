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

#include "Deamer/Language/Type/Definition/Object/Main/Import/FileObjectImport.h"

#include <utility>

deamer::language::type::definition::object::main::FileObjectImport::FileObjectImport(object::main::ImportSyntacticRelation* syntaxRelation_, 
			object::main::ImportFileTarget* target_, 
			object::main::ObjectTarget* objectTarget_)
	: Base(Type::FileObjectImport),
	syntaxRelation(syntaxRelation_),
	target(target_),
	objectTarget(objectTarget_)
{
	references.Add(syntaxRelation);
	references.Add(target);
	references.Add(objectTarget);

}

bool deamer::language::type::definition::object::main::FileObjectImport::operator==(const FileObjectImport& rhs) const noexcept
{
	return this == &rhs || (this->syntaxRelation == rhs.syntaxRelation && this->target == rhs.target && this->objectTarget == rhs.objectTarget && true);
}


deamer::language::type::definition::object::main::FileObjectImport::FileObjectImport() : FileObjectImport(nullptr, 
			nullptr, 
			nullptr)
{
}

