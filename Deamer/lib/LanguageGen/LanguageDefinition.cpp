/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
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