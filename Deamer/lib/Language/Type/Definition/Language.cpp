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

#include "Deamer/Language/Type/Definition/Language.h"
#include <utility>

deamer::language::type::definition::Language::Language(
	std::vector<property::Definition*> propertyDefinitions_,
	std::vector<object::Base*> definitionObjects_, bool temporary_)
	: temporary(temporary_),
	  propertyDefinitions(std::move(propertyDefinitions_)),
	  definitionObjects(std::move(definitionObjects_))
{
}

deamer::language::type::definition::Language::~Language()
{
	if (temporary)
	{
		return;
	}

	for (auto* propertyDefinition : propertyDefinitions)
	{
		delete propertyDefinition;
	}

	for (auto* definitionObject : definitionObjects)
	{
		delete definitionObject;
	}
}
