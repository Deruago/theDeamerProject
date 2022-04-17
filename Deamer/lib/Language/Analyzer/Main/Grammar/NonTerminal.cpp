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

#include "Deamer/Language/Analyzer/Main/Grammar/NonTerminal.h"
#include "Deamer/Language/Reference/ReverseLookup.h"

deamer::language::analyzer::main::NonTerminal::NonTerminal(
	const reference::PropertyDefinitionBase* reference_,
	const reference::LDO<deamer::language::type::definition::object::main::NonTerminal, true>
		nonTerminal_)
	: Base(reference_),
	  nonTerminal(nonTerminal_)
{
}

bool deamer::language::analyzer::main::NonTerminal::IsRecursive(const size_t depth,
																const bool infinite) const
{
	return IsRecursiveImplementation(0, depth, infinite, nonTerminal);
}

bool deamer::language::analyzer::main::NonTerminal::IsDirectRecursive() const
{
	return IsRecursive(0, false);
}

bool deamer::language::analyzer::main::NonTerminal::IsEventuallyRecursive(const size_t depth) const
{
	return IsRecursive(0, true);
}

bool deamer::language::analyzer::main::NonTerminal::DoesNonTerminalHaveValue() const
{
	return true;
}

bool deamer::language::analyzer::main::NonTerminal::IsStartType() const
{
	reference::PropertyDefinition<type::definition::property::Type::Grammar> reference(
		*language_reference);

	const auto& nonTerminals =
		reference.GetDefinition<type::definition::property::Type::Grammar>().NonTerminals;

	if (nonTerminals.empty())
	{
		return false;
	}

	return nonTerminals[0] == nonTerminal;
}

void deamer::language::analyzer::main::NonTerminal::GetStartingTerminals(
	std::set<reference::LDO<type::definition::object::main::Terminal>>& startingTerminals) const
{
	std::set<reference::LDO<type::definition::object::main::NonTerminal>> nonTerminalsVisited;
	GetStartingTerminals(startingTerminals, nonTerminalsVisited);
}

void deamer::language::analyzer::main::NonTerminal::GetEndingTerminals(
	std::set<reference::LDO<type::definition::object::main::Terminal>>& endingTerminals) const
{
	std::set<reference::LDO<type::definition::object::main::NonTerminal>> nonTerminalsVisited;
	GetEndingTerminals(endingTerminals, nonTerminalsVisited);
}

bool deamer::language::analyzer::main::NonTerminal::DoesNonTerminalHaveEmptyAsItsNode() const
{
	std::set<reference::LDO<type::definition::object::main::NonTerminal>> visitedNonTerminals;

	return DoesNonTerminalHaveEmptyAsItsNode(visitedNonTerminals);
}

bool deamer::language::analyzer::main::NonTerminal::CanNonTerminalMatchEmpty() const
{
	std::set<reference::LDO<type::definition::object::main::NonTerminal>> visitedNonTerminals;

	return CanNonTerminalMatchEmpty(visitedNonTerminals);
}

void deamer::language::analyzer::main::NonTerminal::GetLeftNeighboringTokens(
	std::set<type::definition::object::Base*>& neighboringTokens) const
{
	std::set<reference::LDO<type::definition::object::main::NonTerminal>> visitedNonTerminals;

	GetLeftNeighboringTokens(neighboringTokens, visitedNonTerminals);
}

void deamer::language::analyzer::main::NonTerminal::GetLeftNeighboringTokens(
	std::set<type::definition::object::Base*>& neighboringTokens,
	std::set<reference::LDO<type::definition::object::main::NonTerminal>>& visitedNonTerminals)
	const
{
	const reference::ReverseLookup<type::definition::object::main::ProductionRule>
		reverseLookupProductionRules(language_reference);

	const auto& resultReferencingProductionRules = reverseLookupProductionRules.Get(nonTerminal);

	for (const auto& productionRule : resultReferencingProductionRules.GetObjects())
	{
		std::vector<std::size_t> indexes;
		std::size_t currentIndex = 0;
		for (reference::LDO<type::definition::object::main::Terminal> token :
			 productionRule->Tokens)
		{
			if (token == nonTerminal)
			{
				indexes.push_back(currentIndex);
			}

			currentIndex += 1;
		}

		bool topExpanded = false;
		reference::ReverseLookup<type::definition::object::main::NonTerminal>
			reverseLookupProductionRuleNonTerminal(language_reference);
		auto productionRuleTokenResult = reverseLookupProductionRuleNonTerminal.Get(productionRule);
		for (auto index : indexes)
		{
			if (index == 0)
			{
				if (!topExpanded && !productionRuleTokenResult.IsEmpty())
				{
					topExpanded = true;

					if (visitedNonTerminals.find(productionRuleTokenResult.GetObject()) !=
						visitedNonTerminals.end())
					{
						return;
					}

					visitedNonTerminals.insert(productionRuleTokenResult.GetObject());

					NonTerminal(language_reference, productionRuleTokenResult.GetObject())
						.GetLeftNeighboringTokens(neighboringTokens, visitedNonTerminals);

					visitedNonTerminals.erase(productionRuleTokenResult.GetObject());
				}
			}
			else if (index > 0)
			{
				bool shouldBeFurtherAnalyzed = false;
				bool done = false;
				std::size_t currentElementIndex = index - 1;
				do
				{
					auto* const currentToken = productionRule->Tokens[currentElementIndex];
					neighboringTokens.insert(currentToken);

					if (currentToken->Type_ == type::definition::object::Type::NonTerminal &&
						NonTerminal(language_reference, currentToken)
							.DoesNonTerminalHaveEmptyAsItsNode())
					{
						if (currentElementIndex != 0)
						{
							currentElementIndex--;
						}
						else
						{
							shouldBeFurtherAnalyzed = true;
							done = true;
						}
					}
					else
					{
						done = true;
					}
				} while (!done && currentElementIndex >= 0 &&
						 currentElementIndex < productionRule->Tokens.size());

				if (currentElementIndex == 0 && shouldBeFurtherAnalyzed)
				{
					if (!topExpanded && !productionRuleTokenResult.IsEmpty())
					{
						topExpanded = true;

						if (visitedNonTerminals.find(productionRuleTokenResult.GetObject()) !=
							visitedNonTerminals.end())
						{
							return;
						}

						visitedNonTerminals.insert(productionRuleTokenResult.GetObject());

						NonTerminal(language_reference, productionRuleTokenResult.GetObject())
							.GetLeftNeighboringTokens(neighboringTokens, visitedNonTerminals);

						visitedNonTerminals.erase(productionRuleTokenResult.GetObject());
					}
				}
			}
		}
	}
}

void deamer::language::analyzer::main::NonTerminal::GetRightNeighboringTokens(
	std::set<type::definition::object::Base*>& neighboringTokens) const
{
	std::set<reference::LDO<type::definition::object::main::NonTerminal>> visitedNonTerminals;

	GetRightNeighboringTokens(neighboringTokens, visitedNonTerminals);
}

void deamer::language::analyzer::main::NonTerminal::GetRightNeighboringTokens(
	std::set<type::definition::object::Base*>& neighboringTokens,
	std::set<reference::LDO<type::definition::object::main::NonTerminal>>& visitedNonTerminals)
	const
{
	const reference::ReverseLookup<type::definition::object::main::ProductionRule>
		reverseLookupProductionRules(language_reference);

	// Get all production rules that are referencing the analyzed nonterminal.
	const auto& resultReferencingProductionRules = reverseLookupProductionRules.Get(nonTerminal);

	for (const auto& productionRule : resultReferencingProductionRules.GetObjects())
	{
		std::vector<std::size_t> indexes;
		std::size_t currentIndex = 0;
		// Identify self injection of analyzed NonTerminal
		for (reference::LDO<type::definition::object::Base> token : productionRule->Tokens)
		{
			if (token == nonTerminal)
			{
				indexes.push_back(currentIndex);
			}

			currentIndex += 1;
		}

		reference::ReverseLookup<type::definition::object::main::NonTerminal>
			reverseLookupProductionRuleNonTerminal(language_reference);

		// Get all nonterminals that reference this production rule.
		auto productionRuleTokenResult = reverseLookupProductionRuleNonTerminal.Get(productionRule);

		for (auto index : indexes) // Check what is right of our index
		{
			// If index is at the end of the production rule
			if (index == productionRule->Tokens.size() - 1)
			{
				// Check if there is a nonterminal which we can expand to.
				if (!productionRuleTokenResult.IsEmpty())
				{
					if (visitedNonTerminals.find(productionRuleTokenResult.GetObject()) !=
						visitedNonTerminals.end())
					{
						continue;
					}

					visitedNonTerminals.insert(productionRuleTokenResult.GetObject());

					NonTerminal(language_reference, productionRuleTokenResult.GetObject())
						.GetRightNeighboringTokens(neighboringTokens, visitedNonTerminals);

					visitedNonTerminals.erase(productionRuleTokenResult.GetObject());
				}
				else
				{
					// Right hand side is epsilon
				}
			}
			else
			{
				for (auto i = index + 1; i < productionRule->Tokens.size(); i++)
				{
					reference::LDO<type::definition::object::Base> currentToken =
						productionRule->Tokens[i];
					neighboringTokens.insert(currentToken.GetRawPointer());

					if (currentToken->Type_ == type::definition::object::Type::Terminal)
					{
						break;
					}

					NonTerminal nonTerminalAnalyzer(
						language_reference,
						currentToken.Promote<type::definition::object::main::NonTerminal>()
							.GetRawPointer());

					if (!nonTerminalAnalyzer.CanNonTerminalMatchEmpty())
					{
						break;
					}

					if (i == productionRule->Tokens.size() - 1)
					{
						if (visitedNonTerminals.find(productionRuleTokenResult.GetObject()) !=
							visitedNonTerminals.end())
						{
							continue;
						}

						visitedNonTerminals.insert(productionRuleTokenResult.GetObject());

						NonTerminal(language_reference, productionRuleTokenResult.GetObject())
							.GetRightNeighboringTokens(neighboringTokens, visitedNonTerminals);

						visitedNonTerminals.erase(productionRuleTokenResult.GetObject());
					}
				}
			}
		}
	}
}

bool deamer::language::analyzer::main::NonTerminal::DoesNonTerminalHaveEmptyAsItsNode(
	std::set<reference::LDO<type::definition::object::main::NonTerminal>>& visitedNonTerminal) const
{
	if (visitedNonTerminal.find(nonTerminal) != visitedNonTerminal.end())
	{
		return false;
	}

	visitedNonTerminal.insert(nonTerminal);

	for (reference::LDO<type::definition::object::main::ProductionRule> productionrule :
		 nonTerminal->ProductionRules)
	{
		// Definition of having an EMPTY (epsilon) terminal
		if (productionrule->Tokens.empty())
		{
			return true;
		}

		const auto* const lastToken = productionrule->Tokens[productionrule->Tokens.size() - 1];

		if (lastToken->Type_ != type::definition::object::Type::NonTerminal)
		{
			continue;
		}

		reference::LDO<type::definition::object::main::NonTerminal> currentNonTerminal(lastToken);
		NonTerminal analyzer(language_reference, currentNonTerminal.Get());
		if (analyzer.DoesNonTerminalHaveEmptyAsItsNode(visitedNonTerminal))
		{
			return true;
		}
	}

	visitedNonTerminal.erase(nonTerminal);

	return false;
}

bool deamer::language::analyzer::main::NonTerminal::CanNonTerminalMatchEmpty(
	std::set<reference::LDO<type::definition::object::main::NonTerminal>>& visitedNonTerminal) const
{
	if (visitedNonTerminal.find(nonTerminal) != visitedNonTerminal.end())
	{
		return false;
	}

	visitedNonTerminal.insert(nonTerminal);

	for (reference::LDO<type::definition::object::main::ProductionRule> productionrule :
		 nonTerminal->ProductionRules)
	{
		if (productionrule->Tokens.size() > 1)
		{
			// If all tokens can be empty, then this production rule can match empty
			bool continue_ = false;
			for (reference::LDO<type::definition::object::Base> token : productionrule->Tokens)
			{
				if (token->Type_ != type::definition::object::Type::NonTerminal)
				{
					continue_ = true;
					break;
				}

				NonTerminal analyzer(language_reference, token.Get());
				if (!analyzer.CanNonTerminalMatchEmpty(visitedNonTerminal))
				{
					continue_ = true;
					break;
				}
			}

			if (continue_) // Cannot match empty, continuing to next production rule
			{
				continue;
			}

			return true;
		}

		// Definition of having an EMPTY (epsilon) terminal
		if (productionrule->Tokens.empty())
		{
			return true;
		}

		const auto* const token =
			productionrule->Tokens[0]; // Take the token in productionRule there is only 1

		if (token->Type_ != type::definition::object::Type::NonTerminal)
		{
			continue;
		}

		reference::LDO<type::definition::object::main::NonTerminal> currentNonTerminal(token);
		NonTerminal analyzer(language_reference, currentNonTerminal.Get());
		if (analyzer.CanNonTerminalMatchEmpty(visitedNonTerminal))
		{
			return true;
		}
	}

	visitedNonTerminal.erase(nonTerminal);

	return false;
}

void deamer::language::analyzer::main::NonTerminal::GetStartingTerminals(

	std::set<reference::LDO<type::definition::object::main::Terminal>>& startingTerminals,
	std::set<reference::LDO<type::definition::object::main::NonTerminal>>& nonTerminalsVisited)
	const
{
	if (nonTerminalsVisited.find(nonTerminal) != nonTerminalsVisited.end())
	{
		return;
	}
	nonTerminalsVisited.insert(nonTerminal.Get());

	for (reference::LDO<type::definition::object::main::ProductionRule> productionRule :
		 nonTerminal->ProductionRules)
	{
		if (productionRule->Tokens.empty())
		{
			continue;
		}

		size_t i = 0;
		bool isEmptyEnding = false;
		bool done = false;
		do
		{
			isEmptyEnding = false;
			const type::definition::object::Base* firstToken = productionRule->Tokens[i];
			i++;

			if (firstToken->Type_ == type::definition::object::Type::Terminal)
			{
				startingTerminals.insert(firstToken);
				done = true;
			}

			if (firstToken->Type_ == type::definition::object::Type::NonTerminal)
			{
				reference::LDO<type::definition::object::main::NonTerminal> lastTokenAsNT(
					firstToken);
				auto lastTokenAnalyzer = NonTerminal(language_reference, lastTokenAsNT.Get());
				isEmptyEnding = lastTokenAnalyzer.CanNonTerminalMatchEmpty();

				lastTokenAnalyzer.GetStartingTerminals(startingTerminals, nonTerminalsVisited);
			}

		} while (!done && isEmptyEnding && i < productionRule->Tokens.size());
	}

	nonTerminalsVisited.erase(nonTerminal.Get());
}

void deamer::language::analyzer::main::NonTerminal::GetEndingTerminals(
	std::set<reference::LDO<type::definition::object::main::Terminal>>& endingTerminals,
	std::set<reference::LDO<type::definition::object::main::NonTerminal>>& nonTerminalsVisited)
	const
{
	if (nonTerminalsVisited.find(nonTerminal) != nonTerminalsVisited.end())
	{
		return;
	}
	nonTerminalsVisited.insert(nonTerminal.Get());

	for (reference::LDO<type::definition::object::main::ProductionRule> productionRule :
		 nonTerminal->ProductionRules)
	{
		if (productionRule->Tokens.empty())
		{
			continue;
		}

		size_t i = 0;
		bool isEmptyEnding = false;
		bool done = false;
		do
		{
			isEmptyEnding = false;
			i++;
			const type::definition::object::Base* lastToken =
				productionRule->Tokens[productionRule->Tokens.size() - i];

			if (lastToken->Type_ == type::definition::object::Type::Terminal)
			{
				endingTerminals.insert(lastToken);
				done = true;
			}

			if (lastToken->Type_ == type::definition::object::Type::NonTerminal)
			{
				reference::LDO<type::definition::object::main::NonTerminal> lastTokenAsNT(
					lastToken);
				auto lastTokenAnalyzer = NonTerminal(language_reference, lastTokenAsNT.Get());
				isEmptyEnding = lastTokenAnalyzer.DoesNonTerminalHaveEmptyAsItsNode();

				lastTokenAnalyzer.GetEndingTerminals(endingTerminals, nonTerminalsVisited);
			}

		} while (!done && isEmptyEnding && i < productionRule->Tokens.size());
	}

	nonTerminalsVisited.erase(nonTerminal.Get());
}

bool deamer::language::analyzer::main::NonTerminal::IsRecursiveImplementation(
	const size_t currentDepth, const size_t maxDepth, const bool infinite,
	reference::LDO<deamer::language::type::definition::object::main::NonTerminal>
		currentNonTerminal,
	std::set<reference::LDO<deamer::language::type::definition::object::main::NonTerminal>>
		currentVisited) const
{
	for (const auto* const productionRule : currentNonTerminal->ProductionRules)
	{
		for (const auto* const ldo : productionRule->Tokens)
		{
			if (ldo == nonTerminal)
			{
				return true;
			}
		}
	}

	if (currentDepth >= maxDepth && !infinite)
	{
		return false;
	}

	for (const auto* const productionRule : currentNonTerminal->ProductionRules)
	{
		for (reference::LDO<type::definition::object::main::NonTerminal> ldo :
			 productionRule->Tokens)
		{
			if (ldo == nonTerminal)
			{
				return true;
			}

			if (ldo.IsBaseTypeValid() || currentVisited.count(ldo) > 0)
			{
				continue;
			}

			currentVisited.insert(ldo);

			const bool isRecursive = IsRecursiveImplementation(currentDepth + 1, maxDepth, infinite,
															   ldo, currentVisited);

			if (isRecursive)
			{
				return true;
			}
		}
	}

	return false;
}

std::set<deamer::language::type::definition::object::Base*>
deamer::language::analyzer ::main::NonTerminal::GetDirectNonTerminalAndTerminals() const
{
	std::set<::deamer::language::type::definition::object::Base*> symbols;
	GetDirectNonTerminalAndTerminals(symbols);
	return symbols;
}

std::set<deamer::language::type::definition::object::Base*>
deamer::language::analyzer::main::NonTerminal::GetDirectNonTerminalAndTerminals(
	std::set<deamer::language::type::definition::object::Base*>& symbols,
	std::set<reference::LDO<deamer::language::type::definition::object::main::NonTerminal>>
		visitedNonTerminal) const
{
	if (visitedNonTerminal.find(nonTerminal) != visitedNonTerminal.end())
	{
		return {};
	}
	visitedNonTerminal.insert(nonTerminal);

	for (const auto* const productionRule : nonTerminal->ProductionRules)
	{
		for (auto* symbol : productionRule->Tokens)
		{
			symbols.insert(symbol);

			if (symbol->Type_ == type::definition::object::Type::NonTerminal)
			{
				auto nonterminal = ::deamer::language::reference::LDO<
					::deamer::language::type::definition::object::main::NonTerminal>(symbol);

				if (nonterminal->IsInlined())
				{
					auto analyzer = ::deamer::language::analyzer::main::NonTerminal(
						this->language_reference, nonterminal.Get());
					analyzer.GetDirectNonTerminalAndTerminals(symbols, visitedNonTerminal);
				}
			}
		}
	}

	return {};
}
