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

#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <iostream>
#include <algorithm>
#include <utility>

void deamer::LanguageDefinition::IncreaseReferenceCounterOfTokensUsedInRule(const std::vector<Token*>& tokens)
{
	for(auto* token : tokens)
        token->AddReferenceToTokenThatUsesThisToken();
}


deamer::LanguageDefinition::~LanguageDefinition()
{
	for (const auto* node : Nodes)
		delete node;

	for (const auto* type : Types)
		delete type;

	for (const auto* rule : Rules)
		delete rule;
}

void deamer::LanguageDefinition::AddNode(Node* newNode)
{
	if (!IsNodeInVector(newNode))
		Nodes.push_back(newNode);
}

void deamer::LanguageDefinition::AddIgnoredNode(Node* newNode)
{
	if (!IsIgnoredNodeInVector(newNode))
		IgnoreNodes.push_back(newNode);
}

void deamer::LanguageDefinition::AddType(Type* newType)
{
	if (!IsTypeInVector(newType))
		Types.push_back(newType);
}

void deamer::LanguageDefinition::AddRule(Rule* newRule)
{
	if (!IsRuleInVector(newRule))
		Rules.push_back(newRule);
}

void deamer::LanguageDefinition::RemoveType(Type* type)
{
	if(type->TotalAmountOfTypesThatUsesThisToken == 0)
	{
		for(Rule* rule : type->Rules)
		{
            RemoveRule(rule);
		}

		Types.erase(std::remove(Types.begin(), Types.end(), type), Types.end());
	}
}

void deamer::LanguageDefinition::RemoveRule(Rule* rule)
{
	for(Token* token : rule->Tokens)
	{
        token->RemoveReferenceThatUsedThisToken();
        if (token->TokenPermission.has_flag(TokenPermission_t::node))
            RemoveNode(static_cast<Node*>(token));
        else
            RemoveType(static_cast<Type*>(token));
	}
	Rules.erase(std::remove(Rules.begin(), Rules.end(), rule), Rules.end());
}

void deamer::LanguageDefinition::RemoveNode(Node* node)
{
	if (node->TotalAmountOfTypesThatUsesThisToken == 0)
	{
		if (!node->TokenPermission.has_flag(TokenPermission_t::ignore))
			Nodes.erase(std::remove(Nodes.begin(), Nodes.end(), node), Nodes.end());
		else
			IgnoreNodes.erase(std::remove(IgnoreNodes.begin(), IgnoreNodes.end(), node), IgnoreNodes.end());
	}
}

const std::vector<deamer::Node*>& deamer::LanguageDefinition::GetNodes() const
{
	return Nodes;
}

const std::vector<deamer::Node*>& deamer::LanguageDefinition::GetIgnoreNodes() const
{
	return IgnoreNodes;
}

const std::vector<deamer::Type*>& deamer::LanguageDefinition::GetTypes() const
{
	return Types;
}

const std::vector<deamer::Rule*>& deamer::LanguageDefinition::GetRules() const
{
	return Rules;
}

bool deamer::LanguageDefinition::IsNodeInVector(const Node* node) const
{
	for (auto* const node_ : Nodes)
		if (node_ == node)
			return true;
	return false;
}

bool deamer::LanguageDefinition::IsIgnoredNodeInVector(const Node* node) const
{
	for (auto* const node_ : IgnoreNodes)
		if (node_ == node)
			return true;
	return false;
}

bool deamer::LanguageDefinition::IsTypeInVector(const Type* type) const
{
	for (auto* const type_ : Types)
		if (type_ == type)
			return true;
	return false;
}

bool deamer::LanguageDefinition::IsRuleInVector(const Rule* rule) const
{
	for (auto* const rule_ : Rules)
		if (rule_ == rule)
			return true;
	return false;
}