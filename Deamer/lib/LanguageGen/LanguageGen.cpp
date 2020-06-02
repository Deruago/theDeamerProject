#include <iostream>
#include "Deamer/LanguageGen/LanguageGen.h"
#include "Deamer/LanguageGen/Node.h"
#include "Deamer/LanguageGen/Type.h"
#include "Deamer/LanguageGen/Rule.h"

LanguageGen::LanguageGen() {}

LanguageGen::LanguageGen(LexerType_t lexerType, ParserType_t parserType)
{
    LanguageGen::SetLexer(lexerType);
    LanguageGen::SetParser(parserType);
}

Node* LanguageGen::CreateNode(const std::string nodeName, const std::string regex)
{
    Node* newNode = new Node(nodeName, regex);
    Nodes.push_back(newNode);
    return newNode;
}

Type* LanguageGen::CreateType(const std::string typeName)
{
    Type* newType = new Type(typeName);
    Types.push_back(newType);
    return newType;
}

/**
 * The first rule added is the "Start rule" this rule will first be called. All following rules should be linked with this rule.
*/
Rule* LanguageGen::CreateRule(Type* type, const std::vector<Token*> tokens)
{
    Rule* newRule = new Rule(tokens);
    type->AddRule(newRule);
    Rules.push_back(newRule);
    return newRule;
}

void LanguageGen::DeleteAllNodes()
{
    for(auto itr = Nodes.end(); itr != Nodes.begin(); itr--)
    {
        delete *itr;
        *itr = nullptr;
        Nodes.pop_back();
    }
}

void LanguageGen::DeleteAllTypes()
{
    for(auto itr = Types.end(); itr != Types.begin(); itr--)
    {
        delete *itr;
        *itr = nullptr;
        Types.pop_back();
    }
}

void LanguageGen::DeleteAllRules()
{
    for(auto itr = Rules.end(); itr != Rules.begin(); itr--)
    {
        delete *itr;
        *itr = nullptr;
        Rules.pop_back();
    }
}

void LanguageGen::PrintNodes()
{
    for (int i = 0; i < Nodes.size(); i++)
    {
        std::cout << Nodes[i]->TokenName << '\n';
    }
    std::cout << '\n';
}

void LanguageGen::PrintTypes()
{
    for (int i = 0; i < Types.size(); i++)
    {
        std::cout << Types[i]->TokenName << '\n';
    }
    std::cout << '\n';
}

void LanguageGen::PrintRules()
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

void LanguageGen::PrintLanguageConfig()
{
    for(int i = Types.size() - 1; i >= 0; i--)
    {
        Types[i]->PrintToken();
        std::cout << '\n';
        Types[i]->PrintRules();
        std::cout << '\n';
    }
}

void LanguageGen::SetLexer(LexerType_t lexerType)
{
    LanguageGen::Lexer = lexerType;
}

void LanguageGen::SetParser(ParserType_t parserType)
{
    LanguageGen::Parser = parserType;
}