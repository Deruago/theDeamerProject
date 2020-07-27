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

deamer::LanguageDefinition::LanguageDefinition(std::string languageName)
{
    LanguageName = std::move(languageName);
}

std::string deamer::LanguageDefinition::GetLanguageName()
{
    return LanguageName;
}

deamer::Node* deamer::LanguageDefinition::CreateNode(const std::string& nodeName, const std::string& regex, const bool createAst)
{
    Node* newNode = new Node(nodeName, regex, createAst);
    newNode->IgnoreNode = false;
    Nodes.push_back(newNode);
    return newNode;
}

deamer::Node* deamer::LanguageDefinition::IgnoreNode(const std::string& nodeName, const std::string& regex)
{
    Node* newNode = new Node(nodeName, regex, false);
    newNode->IgnoreNode = true;
    IgnoreNodes.push_back(newNode);
    return newNode;
}


deamer::Type* deamer::LanguageDefinition::CreateType(const std::string& typeName, const bool createAst)
{
    Type* newType = new Type(typeName, createAst, false);
    Types.push_back(newType);
    return newType;
}

deamer::Type* deamer::LanguageDefinition::CreateGroupedType(const std::string& typeName, const bool createAst)
{
    Type* newType = new Type(typeName, createAst, true);
    Types.push_back(newType);
    return newType;
}

void deamer::LanguageDefinition::IncreaseReferenceCounterOfTokensUsedInRule(std::vector<Token*> tokens)
{
	for(Token* token : tokens)
	{
        token->AddReferenceToTokenThatUsesThisToken();
	}
}

/**
 * The first rule added is the "Start rule" this rule will first be called. All following rules should be linked with this rule.
*/
deamer::Rule* deamer::LanguageDefinition::CreateRule(Type* type, std::vector<Token*> tokens)
{
    Rule* newRule = new Rule(tokens);
    type->AddRule(newRule);
    Rules.push_back(newRule);
    IncreaseReferenceCounterOfTokensUsedInRule(tokens);
    return newRule;
}

deamer::Rule* deamer::LanguageDefinition::CreateRuleWithOneToken(Type* type, Token* token)
{
    Rule* newRule = new Rule({ token });
    type->AddRule(newRule);
    Rules.push_back(newRule);
    IncreaseReferenceCounterOfTokensUsedInRule({ token });
    return newRule;
}

deamer::Type* deamer::LanguageDefinition::GroupTokens(const std::string& typeName, std::vector<Token*>& tokens)
{
    Type* newGroupedType = nullptr;
	if(!tokens.empty())
	{
        newGroupedType = CreateGroupedType(typeName);
		for(auto& token : tokens)
		{
            CreateRuleWithOneToken(newGroupedType, token)->RuleType = RuleType_t::grouped;
            token->AddBaseToken(newGroupedType);
		}
	}
    return newGroupedType;
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
        if (token->IsNode)
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
		if (!node->IgnoreNode)
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
