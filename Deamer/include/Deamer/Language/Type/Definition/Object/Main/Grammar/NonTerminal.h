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
	 *  \brief NonTerminal symbol, used in grammar definitions.
	 */
	class NonTerminal : public Base
	{
	private:
		friend deamer::type::SafeReserve<NonTerminal>;

	public:
		std::string Name;
		std::vector<ProductionRule*> ProductionRules;
		NonTerminalAbstraction abstraction;
		bool Inline;

		NonTerminal(std::string name_, std::vector<ProductionRule*> productionRules_,
					NonTerminalAbstraction abstraction_ = NonTerminalAbstraction::Standard,
					bool inline_ = false);

		bool operator==(const NonTerminal& rhs) const noexcept;

	public:
		/*!
		 * \fn IsInlined
		 *
		 * \brief Returns whether the NonTerminal should be inlined.
		 *
		 * \details An Inlined nonterminal is not visible for the user, unless explicitly wanted.
		 */
		bool IsInlined() const noexcept;

		/*!
		 * \fn IsReserved
		 *
		 *	\brief Checks if the nonterminal is using a reserved name. E.g. "deamerreserved".
		 */
		bool IsReserved() const noexcept;

	protected:
		NonTerminal();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_GRAMMAR_NONTERMINAL_H
