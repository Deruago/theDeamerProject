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

#include "Deamer/Language/Type/Definition/Object/Main/OOPSyntax/OopLink.h"

#include <utility>

deamer::language::type::definition::object::main::OopLink::OopLink(object::main::ProductionRule* productionRule_, 
			std::vector<object::main::OopConceptLink*> OopConceptLinks_)
	: Base(Type::OopLink),
	productionRule(productionRule_),
	OopConceptLinks(OopConceptLinks_)
{
	references.Add(productionRule);
	references.Add(OopConceptLinks);

}

bool deamer::language::type::definition::object::main::OopLink::operator==(const OopLink& rhs) const noexcept
{
	return this == &rhs || (this->productionRule == rhs.productionRule && this->OopConceptLinks == rhs.OopConceptLinks && true);
}


deamer::language::type::definition::object::main::OopLink::OopLink() : OopLink(nullptr, 
			std::vector<object::main::OopConceptLink*>{})
{
}


