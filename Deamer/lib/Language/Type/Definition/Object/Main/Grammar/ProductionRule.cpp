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

#include "Deamer/Language/Type/Definition/Object/Main/Grammar/ProductionRule.h"
#include "Deamer/Language/Reference/LDO.h"

#include <utility>

deamer::language::type::definition::object::main::ProductionRule::ProductionRule(std::vector<object::Base*> Tokens_)
	: Base(Type::ProductionRule),
	Tokens(Tokens_)
{
	references.Add(Tokens);

}

bool deamer::language::type::definition::object::main::ProductionRule::operator==(const ProductionRule& rhs) const noexcept
{
	return this == &rhs || (this->Tokens == rhs.Tokens && true);
}



bool deamer::language::type::definition::object::main::ProductionRule::IsEmpty() const
{
	return Tokens.empty();
}

std::string deamer::language::type::definition::object::main::ProductionRule::GetText() const
{
	std::string output;
	for (auto* token : Tokens)
	{
		switch (token->Type_)
		{
		case Type::Terminal:
			output += reference::LDO<Terminal>(token)->Name;
			break;
		case Type::NonTerminal:
			output += reference::LDO<NonTerminal>(token)->Name;
			break;
		default:
			break;
		}
		output += " ";
	}

	return output;
}

