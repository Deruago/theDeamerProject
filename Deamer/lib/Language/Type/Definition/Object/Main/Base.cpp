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

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Language/Type/Definition/Language.h"

deamer::language::type::definition::object::Base::Base(const object::Type type_)
{
	Type_ = type_;
}

const deamer::type::vector::LDOMultiVector&
deamer::language::type::definition::object::Base::GetReferences() const
{
	return references;
}

bool deamer::language::type::definition::object::Base::IsInitialized() const
{
	return !isUninitialized;
}

void deamer::language::type::definition::object::Base::SetAsUninitialized()
{
	isUninitialized = true;
}

void deamer::language::type::definition::object::Base::Register(Language& language) const
{
	for (const auto& SetOfReferences : references)
	{
		for (const auto* reference : SetOfReferences.second)
		{
			language.cache.Register(this, Type_, reference);
		}
	}
}
