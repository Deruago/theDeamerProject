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

#include "Deamer/Language/Analyzer/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Analyzer/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Reference/ReverseLookup.h"

deamer::language::analyzer::main::Terminal::Terminal(
	const reference::PropertyDefinitionBase* reference_,
	reference::LDO<type::definition::object::main::Terminal> terminal_)
	: Base(reference_),
	  terminal(terminal_)
{
}

bool deamer::language::analyzer::main::Terminal::DoesTerminalHaveValue() const
{
	return terminal->Special == type::definition::object::main::SpecialType::Standard ||
		   terminal->Special == type::definition::object::main::SpecialType::NoValue;
}

void deamer::language::analyzer::main::Terminal::GetAllPossibleNeighbouringTerminals(
	std::set<reference::LDO<type::definition::object::main::Terminal>>& neighbouringTerminals) const
{
	const auto reverseLookupProductionRule = language::reference::ReverseLookup<
		language::type::definition::object::main::ProductionRule>(language_reference);

	const auto result = reverseLookupProductionRule.Get(terminal);
	for (auto& productionRule : result.GetObjects())
	{
		std::vector<std::size_t> indexes;
		std::size_t currentIndex = 0;
		for (reference::LDO<type::definition::object::main::Terminal> token :
			 productionRule->Tokens)
		{
			if (token == terminal)
			{
				indexes.push_back(currentIndex);
			}

			currentIndex += 1;
		}

		for (const std::size_t index : indexes)
		{
			// Check all possible left subtrees
			if (index == 0)
			{
				reference::ReverseLookup<type::definition::object::main::NonTerminal>
					reverseLookupNonterminal(language_reference);
				const auto resultNonTerminal = reverseLookupNonterminal.Get(productionRule.Get());
				if (resultNonTerminal.IsEmpty())
				{
					continue;
				}

				auto nonterminal = resultNonTerminal.GetObject();
				NonTerminal nonTerminalAnalyzer(language_reference, nonterminal.Get());
				std::set<type::definition::object::Base*> neighboringTokens;
				nonTerminalAnalyzer.GetLeftNeighboringTokens(neighboringTokens);

				for (const auto* const neighboringToken : neighboringTokens)
				{
					if (neighboringToken->Type_ ==
						language::type::definition::object::Type::NonTerminal)
					{
						NonTerminal neighborNonTerminalAnalyzer(language_reference,
																neighboringToken);
						neighborNonTerminalAnalyzer.GetEndingTerminals(neighbouringTerminals);
					}
					else if (neighboringToken->Type_ ==
							 language::type::definition::object::Type::Terminal)
					{
						neighbouringTerminals.insert(neighboringToken);
					}
				}
			}

			// Check all possible right subtrees
			if (index == productionRule->Tokens.size() - 1)
			{
				reference::ReverseLookup<type::definition::object::main::NonTerminal>
					reverseLookupNonterminal(language_reference);
				const auto resultNonTerminal = reverseLookupNonterminal.Get(productionRule.Get());
				if (resultNonTerminal.IsEmpty())
				{
					continue;
				}

				auto nonterminal = resultNonTerminal.GetObject();
				NonTerminal nonTerminalAnalyzer(language_reference, nonterminal.Get());
				std::set<type::definition::object::Base*> neighboringTokens;
				nonTerminalAnalyzer.GetRightNeighboringTokens(neighboringTokens);

				for (const auto* const neighboringToken : neighboringTokens)
				{
					if (neighboringToken->Type_ ==
						language::type::definition::object::Type::NonTerminal)
					{
						NonTerminal neighborNonTerminalAnalyzer(language_reference,
																neighboringToken);
						neighborNonTerminalAnalyzer.GetStartingTerminals(neighbouringTerminals);
					}
					else if (neighboringToken->Type_ ==
							 language::type::definition::object::Type::Terminal)
					{
						neighbouringTerminals.insert(neighboringToken);
					}
				}
			}

			// Check the right subtree
			if (index >= 0 && index < productionRule->Tokens.size() - 1)
			{
				const auto* const tokenRight = productionRule->Tokens[index + 1];

				if (tokenRight->Type_ == language::type::definition::object::Type::Terminal)
				{
					neighbouringTerminals.insert(tokenRight);
				}
				else if (tokenRight->Type_ == language::type::definition::object::Type::NonTerminal)
				{
					NonTerminal nonTerminalAnalyzer(language_reference, tokenRight);
					nonTerminalAnalyzer.GetStartingTerminals(neighbouringTerminals);
				}
			}

			// Check the left subtree
			if (index > 0 && index < productionRule->Tokens.size())
			{
				const auto* const tokenLeft = productionRule->Tokens[index - 1];

				if (tokenLeft->Type_ == language::type::definition::object::Type::Terminal)
				{
					neighbouringTerminals.insert(tokenLeft);
				}
				else if (tokenLeft->Type_ == language::type::definition::object::Type::NonTerminal)
				{
					NonTerminal nonTerminalAnalyzer(language_reference, tokenLeft);
					nonTerminalAnalyzer.GetEndingTerminals(neighbouringTerminals);
				}
			}
		}
	}
}
