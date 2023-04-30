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

#include "Deamer/Parser/Type/Dparse/ParserDefinitionRecursiveDescent.h"
#include "Deamer/Template/Parser/Dparse/RecursiveDescent/RecursiveDescentTemplate.h"
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <tuple>
#include <vector>

using namespace deamer::language::reference;
using namespace deamer::language::type::definition::object;
using namespace main;

deamer::parser::type::dparse::ParserDefinitionRecursiveDescent::ParserDefinitionRecursiveDescent(
	const generator::dparse::Dparse::ReferenceType reference_)
	: reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .GetName()
			   ->value)
{
}

std::string deamer::parser::type::dparse::ParserDefinitionRecursiveDescent::Generate() const
{
	templates::dparse::parser::RecursiveDescentTemplate recursiveDescentTemplate;

	recursiveDescentTemplate.language_name_->Set(name);

	if (reference.GetDefinition<language::type::definition::property::Type::Generation>()
			.IsIntegrationSet({tool::type::Tool::Dleg, tool::type::Tool::Dparse}))
	{
		recursiveDescentTemplate.optional_dleg_include_->Set(
			recursiveDescentTemplate.dleg_include_);
		recursiveDescentTemplate.optional_dleg_usage_->Set(recursiveDescentTemplate.dleg_usage_);
	}

	bool first = true;

	for (LDO<NonTerminal> nonterminal :
		 reference.GetDefinition<language::type::definition::property::Type::Grammar>()
			 .NonTerminals)
	{
		recursiveDescentTemplate.production_rule_impl_->variable_field_->Clear();
		if (first)
		{
			first = false;
			recursiveDescentTemplate.start_node_->Set(nonterminal->Name);
		}

		recursiveDescentTemplate.nonterminal_name_->Set(nonterminal->Name);
		std::size_t id = 0;
		std::map<LDO<ProductionRule>, std::size_t> mapProductionRuleWithId;
		std::map<LDO<ProductionRule>, std::set<std::vector<LDO<Terminal>>>>
			mapProductionRuleWithLookahead;
		std::map<LDO<ProductionRule>, std::vector<std::vector<LDO<Terminal>>>>
			mapProductionRuleWithLookaheadSimplified;
		std::optional<LDO<ProductionRule>> epsilonProductionRule;

		const auto& productionRules = nonterminal->ProductionRules;
		for (LDO<ProductionRule> productionRule : productionRules)
		{
			mapProductionRuleWithId.insert({productionRule, id});
			id += 1;

			if (productionRule->IsEmpty())
			{
				epsilonProductionRule = productionRule;
				continue;
			}

			mapProductionRuleWithLookahead.insert({productionRule, {}});

			// This is used to maintain each branch that may provide new lookahead sequences
			std::set<std::tuple<LDO<ProductionRule>, std::size_t, std::vector<LDO<Terminal>>,
								std::vector<std::tuple<LDO<ProductionRule>, std::size_t>>>>
				lookaheadBranchesOfProductionRule;
			lookaheadBranchesOfProductionRule.insert(
				std::make_tuple<LDO<ProductionRule>, std::size_t, std::vector<LDO<Terminal>>,
								std::vector<std::tuple<LDO<ProductionRule>, std::size_t>>>(
					language::reference::LDO<ProductionRule>{productionRule}, 0, {}, {}));

			for (std::size_t i = 0; i < fixedLookAhead; i++)
			{
				std::set<std::tuple<LDO<ProductionRule>, std::size_t, std::vector<LDO<Terminal>>,
									std::vector<std::tuple<LDO<ProductionRule>, std::size_t>>>>
					newLookaheadBranches;
				for (auto [productionRuleBranch, lookAhead, lookAheadTerminalsProducedByBranch,
						   parentProductions] : lookaheadBranchesOfProductionRule)
				{
				reinitialize:
					if ((lookAhead + 1) > productionRuleBranch->Tokens.size())
					{
						if (parentProductions.empty())
						{
							// Remove the branch by skipping, as it is finished
							// Take the produced terminal lookaheads
							mapProductionRuleWithLookahead.find(productionRule)
								->second.insert(lookAheadTerminalsProducedByBranch);
							continue;
						}

						// Re-assign the lookahead and production rule branch and parent list
						productionRuleBranch =
							std::get<LDO<ProductionRule>>(*std::rbegin(parentProductions));
						lookAhead = std::get<std::size_t>(*std::rbegin(parentProductions));
						parentProductions.pop_back(); // Remove last element

						// Re-try
						goto reinitialize;
					}

					// This is the new token
					LDO<Base> currentToken = productionRuleBranch->Tokens[lookAhead];
					bool topEmptyWithParentCalled = false;
					if (currentToken->Type_ == Type::NonTerminal)
					{
						// Identify all possible starting production rules
						// This is a closure operation
						auto currentNonTerminal = currentToken.Promote<NonTerminal>();

						for (auto currentProduction : currentNonTerminal->ProductionRules)
						{
							if (currentProduction->IsEmpty())
							{
								// Nonterminal may be optional
								// Create new entry with lookahead expanded
								newLookaheadBranches.insert(
									std::make_tuple<
										LDO<ProductionRule>, std::size_t,
										std::vector<LDO<Terminal>>,
										std::vector<std::tuple<LDO<ProductionRule>, std::size_t>>>(
										language::reference::LDO<ProductionRule>{
											productionRuleBranch},
										lookAhead + 1,
										{lookAheadTerminalsProducedByBranch.begin(),
										 lookAheadTerminalsProducedByBranch.end()},
										{parentProductions.begin(), parentProductions.end()}));
								continue;
							}

							LDO<Base> currentEvaluatedToken = currentProduction->Tokens[0];
							if (currentEvaluatedToken->Type_ == Type::NonTerminal)
							{
								// Look further
								// Note this can cause issues with left-recursion
								// To avoid, simply ignore branches that from this point
								// re-enter newly occured sub-parent
								//
								// Direct left-recursion
								// A := A C
								//
								// A := B C
								// B := A D
								// Indirect left-recursion, there is a path of NTs
								// from A -> A
								//
								// The analysis requires Complete expansion of every branch
								auto currentEvaluatedNonTerminal =
									currentEvaluatedToken.Promote<NonTerminal>();
								// Production Branch, with parents constructed since entry
								std::vector<
									std::tuple<LDO<ProductionRule>, std::vector<LDO<NonTerminal>>,
											   std::vector<LDO<ProductionRule>>>>
									evaluatedProductionRules;

								for (auto productionRule :
									 currentEvaluatedNonTerminal->ProductionRules)
								{
									evaluatedProductionRules.push_back(
										std::make_tuple<LDO<ProductionRule>,
														std::vector<LDO<NonTerminal>>,
														std::vector<LDO<ProductionRule>>>(
											productionRule, {}, {currentProduction}));
								}

								while (!evaluatedProductionRules.empty())
								{
									std::vector<std::tuple<LDO<ProductionRule>,
														   std::vector<LDO<NonTerminal>>,
														   std::vector<LDO<ProductionRule>>>>
										newEvaluatedProductionRules;

									for (auto [evaluatedProductionRule, newParents,
											   newParentProductions] : evaluatedProductionRules)
									{
										if (evaluatedProductionRule->IsEmpty())
										{
											auto newLookAheadTerminalsProducedByBranch =
												lookAheadTerminalsProducedByBranch;

											auto newProductionParents = parentProductions;
											newProductionParents.emplace_back(productionRuleBranch,
																			  lookAhead + 1);
											for (auto productionParent : newParentProductions)
											{
												newProductionParents.emplace_back(productionParent,
																				  1);
											}

											newLookaheadBranches.insert(
												std::make_tuple<
													LDO<ProductionRule>, std::size_t,
													std::vector<LDO<Terminal>>,
													std::vector<std::tuple<LDO<ProductionRule>,
																		   std::size_t>>>(
													language::reference::LDO<ProductionRule>{
														evaluatedProductionRule},
													1, // New entered production rule starts at 1
													   // next turn
													{newLookAheadTerminalsProducedByBranch.begin(),
													 newLookAheadTerminalsProducedByBranch.end()},
													{newProductionParents.begin(),
													 newProductionParents.end()}));
											continue;
										}

										if (std::find(newParents.begin(), newParents.end(),
													  evaluatedProductionRule->Tokens[0]) !=
											newParents.end())
										{
											// Left-recursion, this branch is useless now
											continue;
										}

										// No left-recursion in this branch
										// It can be advanced
										if (evaluatedProductionRule->Tokens[0]->Type_ ==
											Type::Terminal)
										{
											// TERMINAL, Construct result and continue
											auto newLookAheadTerminalsProducedByBranch =
												lookAheadTerminalsProducedByBranch;

											auto newProductionParents = parentProductions;
											newProductionParents.emplace_back(productionRuleBranch,
																			  lookAhead + 1);
											for (auto productionParent : newParentProductions)
											{
												newProductionParents.emplace_back(productionParent,
																				  1);
											}

											newLookAheadTerminalsProducedByBranch.emplace_back(
												evaluatedProductionRule->Tokens[0]);
											newLookaheadBranches.insert(
												std::make_tuple<
													LDO<ProductionRule>, std::size_t,
													std::vector<LDO<Terminal>>,
													std::vector<std::tuple<LDO<ProductionRule>,
																		   std::size_t>>>(
													language::reference::LDO<ProductionRule>{
														evaluatedProductionRule},
													1, // New entered production rule starts at 1
													   // next turn
													{newLookAheadTerminalsProducedByBranch.begin(),
													 newLookAheadTerminalsProducedByBranch.end()},
													{newProductionParents.begin(),
													 newProductionParents.end()}));
										}
										else
										{
											// Nonterminal, expand the productions inside this
											// nonterminal And add to closure
											auto subNonTerminal = LDO<NonTerminal>(
												evaluatedProductionRule->Tokens[0]);
											auto newNonTerminalParents = newParents;
											newNonTerminalParents.push_back(subNonTerminal);
											auto newProductionParentsLocal = newParentProductions;
											newProductionParentsLocal.push_back(
												evaluatedProductionRule);

											for (auto subProduction :
												 subNonTerminal->ProductionRules)
											{
												newEvaluatedProductionRules.push_back(
													std::make_tuple<
														LDO<ProductionRule>,
														std::vector<LDO<NonTerminal>>,
														std::vector<LDO<ProductionRule>>>(
														subProduction,
														{newNonTerminalParents.begin(),
														 newNonTerminalParents.end()},
														{newProductionParentsLocal.begin(),
														 newProductionParentsLocal.end()}));
											}
										}
									}

									evaluatedProductionRules = newEvaluatedProductionRules;
								}
							}
							else if (currentEvaluatedToken->Type_ == Type::Terminal)
							{
								// Production branch is finished
								auto currentEvaluatedTerminal =
									currentEvaluatedToken.Promote<Terminal>();
								auto newLookAheadTerminalsProducedByBranch =
									lookAheadTerminalsProducedByBranch;

								auto newProductionParents = parentProductions;
								newProductionParents.emplace_back(productionRuleBranch,
																  lookAhead + 1);

								newLookAheadTerminalsProducedByBranch.push_back(
									currentEvaluatedTerminal);
								newLookaheadBranches.insert(
									std::make_tuple<
										LDO<ProductionRule>, std::size_t,
										std::vector<LDO<Terminal>>,
										std::vector<std::tuple<LDO<ProductionRule>, std::size_t>>>(
										language::reference::LDO<ProductionRule>{currentProduction},
										1,
										{newLookAheadTerminalsProducedByBranch.begin(),
										 newLookAheadTerminalsProducedByBranch.end()},
										{newProductionParents.begin(),
										 newProductionParents.end()}));
							}
						}
					}
					else if (currentToken->Type_ == Type::Terminal)
					{
						// Simply add the terminal as lookahead
						// , and advance this branch.
						auto currentTerminal = currentToken.Promote<Terminal>();

						lookAheadTerminalsProducedByBranch.push_back(currentTerminal);
						newLookaheadBranches.insert(
							std::make_tuple<
								LDO<ProductionRule>, std::size_t, std::vector<LDO<Terminal>>,
								std::vector<std::tuple<LDO<ProductionRule>, std::size_t>>>(
								language::reference::LDO<ProductionRule>{productionRuleBranch},
								lookAhead + 1,
								{lookAheadTerminalsProducedByBranch.begin(),
								 lookAheadTerminalsProducedByBranch.end()},
								{parentProductions.begin(), parentProductions.end()}));
					}

					if (topEmptyWithParentCalled)
					{
						// Split the production branch in two ways:
						// - Terminating
						// - Non-terminating
					}
				}

				lookaheadBranchesOfProductionRule = newLookaheadBranches;
			}

			for (auto [productionRuleBranch, lookAhead, lookAheadTerminalsProducedByBranch,
					   parentProductions] : lookaheadBranchesOfProductionRule)
			{
				mapProductionRuleWithLookahead.find(productionRule)
					->second.insert(lookAheadTerminalsProducedByBranch);
			}
		}

		auto processProductionRule = [&](LDO<ProductionRule> productionRule,
										 std::size_t lookaheadId) {
			recursiveDescentTemplate.expect_node_->variable_field_->Clear();
			recursiveDescentTemplate.peeked_nonterminal_->variable_field_->Clear();

			recursiveDescentTemplate.production_rule_id_->Set(
				std::to_string(mapProductionRuleWithId.find(productionRule)->second));

			// Implement production rule local lookahead
			// Ensure to take as many lookahead as possible,
			// In case of ambiguity notify user, however, do produce parser
			if (productionRule->IsEmpty())
			{
				recursiveDescentTemplate.production_rule_impl_->Set(
					recursiveDescentTemplate.epsilon_production_rule_impl_);
			}
			else
			{
				recursiveDescentTemplate.production_rule_impl_->Set(
					recursiveDescentTemplate.general_production_rule_impl_);

				auto& lookaheads = mapProductionRuleWithLookaheadSimplified.find(productionRule)
									   ->second[lookaheadId];
				for (auto& lookahead : lookaheads)
				{
					recursiveDescentTemplate.peeked_nonterminal_name_->Set(lookahead->Name);
					recursiveDescentTemplate.peeked_nonterminal_->ExpandVariableField();
				}
			}

			for (LDO<Base> token : productionRule->Tokens)
			{
				if (token->Type_ == Type::NonTerminal)
				{
					auto nonterminal = token.Promote<NonTerminal>();
					recursiveDescentTemplate.expect_token_name_->Set(nonterminal->Name);
					recursiveDescentTemplate.expect_node_->Set(
						recursiveDescentTemplate.expect_node_nonterminal_);
				}
				else if (token->Type_ == Type::Terminal)
				{
					auto terminal = token.Promote<Terminal>();
					recursiveDescentTemplate.expect_token_name_->Set(terminal->Name);
					if (terminal->Special == SpecialType::Ignore ||
						terminal->Special == SpecialType::Delete)
					{
						recursiveDescentTemplate.expect_node_->Set(
							recursiveDescentTemplate.expect_node_ignored_or_deleted_terminal_);
					}
					else
					{
						recursiveDescentTemplate.expect_node_->Set(
							recursiveDescentTemplate.expect_node_included_terminal_);
					}
				}
				else
				{
					// Issue in the LPD
					continue;
				}

				recursiveDescentTemplate.expect_node_->ExpandVariableField();
			}

			recursiveDescentTemplate.production_rule_impl_->ExpandVariableField();
		};

		std::vector<std::tuple<LDO<ProductionRule>, std::size_t>> prioritizedProductionRules;

		/* Adaptive Recursive Descent lookahead
		 *	- RD(k)
		 *	- Identify production rules with equivalent lookahead
		 *	- Specialize lookahead of both production rules
		 *	- In case after some constant no specialization progress is made
		 *		- Declare ambiguous
		 *		- Continue with other pairs
		 */
		if (false)
		{
			for (auto& productionRule : productionRules)
			{
				auto iter = mapProductionRuleWithLookahead.find(productionRule);
				for (auto lookAheadSequence : iter->second)
				{
					for (auto otherProductionRule : productionRules)
					{
						if (otherProductionRule == productionRule)
						{
							continue;
						}

						auto otherIter = mapProductionRuleWithLookahead.find(otherProductionRule);
						for (auto otherLookAheadSequence : otherIter->second)
						{
							if (lookAheadSequence == otherLookAheadSequence)
							{
								// Specialize both sequences
							}
						}
					}
				}
			}
		}

		std::size_t maxLookaheadEncountered = fixedLookAhead;
		for (auto& [productionRule, lookaheads] : mapProductionRuleWithLookahead)
		{
			mapProductionRuleWithLookaheadSimplified.insert({productionRule, {}});
			auto& thisLookaheads =
				mapProductionRuleWithLookaheadSimplified.find(productionRule)->second;

			for (auto& lookahead : lookaheads)
			{
				if (lookahead.size() > maxLookaheadEncountered)
				{
					maxLookaheadEncountered = lookahead.size();
				}
				thisLookaheads.push_back(lookahead);
			}
		}

		// Order by length
		for (int i = maxLookaheadEncountered; i >= 0; i--)
		{
			for (auto& [productionRule, lookaheads] : mapProductionRuleWithLookahead)
			{
				std::size_t id = 0;
				for (auto& lookahead : lookaheads)
				{
					if (lookahead.size() != i)
					{
						id++;
						continue;
					}

					prioritizedProductionRules.emplace_back(productionRule, id);
					id++;
				}
			}
		}

		for (auto [productionRule, lookaheadId] : prioritizedProductionRules)
		{
			processProductionRule(productionRule, lookaheadId);
		}

		if (epsilonProductionRule.has_value())
		{
			processProductionRule(epsilonProductionRule.value(),
								  std::numeric_limits<std::size_t>::max());
		}

		recursiveDescentTemplate.non_terminal_impl_->ExpandVariableField();
	}

	return recursiveDescentTemplate.GetOutput();
}
