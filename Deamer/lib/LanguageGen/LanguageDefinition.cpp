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
    Nodes.push_back(newNode);
    return newNode;
}

deamer::Node* deamer::LanguageDefinition::IgnoreNode(const std::string& nodeName, const std::string& regex)
{
    Node* newNode = new Node(nodeName, regex, false);
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

/**
 * The first rule added is the "Start rule" this rule will first be called. All following rules should be linked with this rule.
*/
deamer::Rule* deamer::LanguageDefinition::CreateRule(Type* type, const std::vector<Token*>& tokens)
{
    Rule* newRule = new Rule(tokens);
    type->AddRule(newRule);
    Rules.push_back(newRule);
    return newRule;
}

deamer::Type* deamer::LanguageDefinition::GroupTokens(const std::string& typeName, const std::vector<Token*>& tokens)
{
    Type* newGroupedType = nullptr;
	if(!tokens.empty())
	{
        newGroupedType = CreateGroupedType(typeName);
		for(auto& token : tokens)
		{
            CreateRule(newGroupedType, { token });
            token->AddBaseToken(newGroupedType);
		}
	}
    return newGroupedType;
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
