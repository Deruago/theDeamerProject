#include <iostream>
#include "Deamer/LanguageGen/LanguageDefinition.h"

Node* LanguageDefinition::CreateNode(const std::string nodeName, const std::string regex)
{
    Node* newNode = new Node(nodeName, regex);
    Nodes.push_back(newNode);
    return newNode;
}

Type* LanguageDefinition::CreateType(const std::string typeName)
{
    Type* newType = new Type(typeName);
    Types.push_back(newType);
    return newType;
}

/**
 * The first rule added is the "Start rule" this rule will first be called. All following rules should be linked with this rule.
*/
Rule* LanguageDefinition::CreateRule(Type* type, const std::vector<Token*> tokens)
{
    Rule* newRule = new Rule(tokens);
    type->AddRule(newRule);
    Rules.push_back(newRule);
    return newRule;
}

void LanguageDefinition::DeleteAllNodes()
{
    for(auto itr = Nodes.end(); itr != Nodes.begin(); itr--)
    {
        delete *itr;
        *itr = nullptr;
        Nodes.pop_back();
    }
}

void LanguageDefinition::DeleteAllTypes()
{
    for(auto itr = Types.end(); itr != Types.begin(); itr--)
    {
        delete *itr;
        *itr = nullptr;
        Types.pop_back();
    }
}

void LanguageDefinition::DeleteAllRules()
{
    for(auto itr = Rules.end(); itr != Rules.begin(); itr--)
    {
        delete *itr;
        *itr = nullptr;
        Rules.pop_back();
    }
}

void LanguageDefinition::PrintNodes()
{
    for (int i = 0; i < Nodes.size(); i++)
    {
        std::cout << Nodes[i]->TokenName << '\n';
    }
    std::cout << '\n';
}

void LanguageDefinition::PrintTypes()
{
    for (int i = 0; i < Types.size(); i++)
    {
        std::cout << Types[i]->TokenName << '\n';
    }
    std::cout << '\n';
}

void LanguageDefinition::PrintRules()
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

void LanguageDefinition::PrintLanguageConfig()
{
    for(int i = Types.size() - 1; i >= 0; i--)
    {
        Types[i]->PrintToken();
        std::cout << '\n';
        Types[i]->PrintRules();
        std::cout << '\n';
    }
}