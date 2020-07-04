#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <iostream>

deamer::LanguageDefinition::LanguageDefinition(std::string languageName)
{
    deamer::LanguageDefinition::LanguageName = languageName;
}

std::string deamer::LanguageDefinition::GetLanguageName()
{
    return deamer::LanguageDefinition::LanguageName;
}

deamer::Node* deamer::LanguageDefinition::CreateNode(const std::string nodeName, const std::string regex, const bool createAst)
{
    deamer::Node* newNode = new Node(nodeName, regex, createAst);
    Nodes.push_back(newNode);
    return newNode;
}

deamer::Type* deamer::LanguageDefinition::CreateType(const std::string typeName, const bool createAst)
{
    deamer::Type* newType = new Type(typeName, createAst);
    Types.push_back(newType);
    return newType;
}

/**
 * The first rule added is the "Start rule" this rule will first be called. All following rules should be linked with this rule.
*/
deamer::Rule* deamer::LanguageDefinition::CreateRule(Type* type, const std::vector<Token*> tokens)
{
    deamer::Rule* newRule = new Rule(tokens);
    type->AddRule(newRule);
    Rules.push_back(newRule);
    return newRule;
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