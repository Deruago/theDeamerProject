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

#include "Deamer/Language/Type/Definition/Object/Main/Value/ValueObject.h"

#include <utility>

deamer::language::type::definition::object::main::ValueObject::ValueObject(object::main::ValueObjectType ruleType_, 
			std::string ruleName_, 
			std::vector<object::Base*> syntacticRelations_, 
			std::vector<object::main::ValueAbstraction*> valueAbstractions_)
	: Base(Type::ValueObject),
	ruleType(ruleType_),
	ruleName(ruleName_),
	syntacticRelations(syntacticRelations_),
	valueAbstractions(valueAbstractions_)
{
	references.Add(syntacticRelations);
	references.Add(valueAbstractions);

}

bool deamer::language::type::definition::object::main::ValueObject::operator==(const ValueObject& rhs) const noexcept
{
	return this == &rhs || (this->ruleType == rhs.ruleType && this->ruleName == rhs.ruleName && this->syntacticRelations == rhs.syntacticRelations && this->valueAbstractions == rhs.valueAbstractions && true);
}


deamer::language::type::definition::object::main::ValueObject::ValueObject() : ValueObject(object::main::ValueObjectType::reserved_default_enum_option, 
			"", 
			std::vector<object::Base*>{}, 
			std::vector<object::main::ValueAbstraction*>{})
{
}


