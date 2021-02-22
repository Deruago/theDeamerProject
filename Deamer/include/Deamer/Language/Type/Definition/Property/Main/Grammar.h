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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_GRAMMAR_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_GRAMMAR_H


#include "Deamer/Language/Type/Definition/Property/Main/Definition.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Grammar/ProductionRule.h"
#include <vector>

namespace deamer::language::type::definition::property::main {
	/*! \class Grammar
	 *
	 *  Language Property Definition of a grammar, used to define the grammar for language x.
	 */
	class Grammar final : public Definition
	{
	public:
		std::vector<object::main::NonTerminal*> NonTerminals;
		std::vector<object::main::ProductionRule*> ProductionRules;
		
		Grammar(std::vector<object::main::NonTerminal*> nonTerminals_, std::vector<object::main::ProductionRule*> productionRules_);

		Grammar(const Grammar& lexicon) = delete;
		Grammar(Grammar&& lexicon) = delete;

		void operator=(const Grammar& lexicon) = delete;
		void operator=(Grammar&& lexicon) = delete;

		~Grammar() = default;
	};
}

#endif //DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_GRAMMAR_H