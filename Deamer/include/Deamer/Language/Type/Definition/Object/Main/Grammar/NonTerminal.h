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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_GRAMMAR_NONTERMINAL_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_GRAMMAR_NONTERMINAL_H

#include "Deamer/Language/Type/Definition/Object/Base.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminalAbstraction.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/ProductionRule.h"
#include "Deamer/Type/Memory/SafeReserve.h"
#include <string>
#include <vector>

namespace deamer::language::type::definition::object::main
{
	/*! \class NonTerminal
	 *
	 *  NonTerminal symbol, used in grammar definitions.
	 */
	class NonTerminal : public Base
	{
	private:
		friend deamer::type::SafeReserve<NonTerminal>;

	public:
		std::string Name;
		std::vector<ProductionRule*> ProductionRules;
		NonTerminalAbstraction abstraction;

		NonTerminal(std::string name_, std::vector<ProductionRule*> productionRules_,
					NonTerminalAbstraction abstraction_ = NonTerminalAbstraction::Standard);

		bool operator==(const NonTerminal& rhs) const
		{
			return this == &rhs ||
				   (this->Name == rhs.Name && this->ProductionRules == rhs.ProductionRules);
		}

	private:
		NonTerminal();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_GRAMMAR_NONTERMINAL_H
