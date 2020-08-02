/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <iostream>
#include <algorithm>
#include <utility>

void deamer::LanguageDefinition::IncreaseReferenceCounterOfTokensUsedInRule(std::vector<Token*> tokens)
{
	for(Token* token : tokens)
        token->AddReferenceToTokenThatUsesThisToken();
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

void deamer::LanguageDefinition::DeleteAllNodes()
{
    for(auto itr = Nodes.end(); itr != Nodes.begin(); itr--)
    {
        delete *itr;
        *itr = nullptr;
        Nodes.pop_back();
    }
}

void deamer::LanguageDefinition::DeleteAllTypes()
{
    for(auto itr = Types.end(); itr != Types.begin(); itr--)
    {
        delete *itr;
        *itr = nullptr;
        Types.pop_back();
    }
}

void deamer::LanguageDefinition::DeleteAllRules()
{
    for(auto itr = Rules.end(); itr != Rules.begin(); itr--)
    {
        delete *itr;
        *itr = nullptr;
        Rules.pop_back();
    }
}

void deamer::LanguageDefinition::PrintNodes()
{
    for (int i = 0; i < Nodes.size(); i++)
    {
        std::cout << Nodes[i]->TokenName << '\n';
    }
    std::cout << '\n';
}

void deamer::LanguageDefinition::PrintTypes()
{
    for (int i = 0; i < Types.size(); i++)
    {
        std::cout << Types[i]->TokenName << '\n';
    }
    std::cout << '\n';
}

void deamer::LanguageDefinition::PrintRules()
{
    for (int i = 0; i < Rules.size(); i++)
    {
        for(int j = 0; j < Rules[i]->Tokens.size(); j++)
        {
            std::cout << Rules[i]->Tokens[j]->TokenName << ' ';
        }
        std::cout << '\n';
    }
}

bool deamer::LanguageDefinition::TypeIsStartType(Type* type)
{
    return type->TokenType.has_flag(TokenType_t::start);
}

void deamer::LanguageDefinition::PrintLanguageConfig()
{
    for(int i = Types.size() - 1; i >= 0; i--)
    {
        Types[i]->PrintToken();
        std::cout << '\n';
        Types[i]->PrintRules();
        std::cout << '\n';
    }
}
