#ifndef DEAMER_LANGUAGEGEN_LANGUAGEGEN_H
#define DEAMER_LANGUAGEGEN_LANGUAGEGEN_H

#include <string>
#include <vector>
#include "Deamer/Deamer.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/Node.h"
#include "Deamer/LanguageGen/Type.h"
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Rule.h"

/*
This header describes the class implementation of LanguageGen. Which is used to generate Types, Nodes and Rules
*/
using namespace Deamer;

class LanguageGen
{
    std::vector<Node*> Nodes;
    std::vector<Type*> Types;
    std::vector<Rule*> Rules;
    LexerType_t Lexer;
    ParserType_t Parser;

    public:
        LanguageGen();
        LanguageGen(LexerType_t lexerType, ParserType_t parserType);
        Node* CreateNode(const std::string nodeName, const std::string regex); // Used to create a Node Class
        Type* CreateType(const std::string typeName); // Used to create a Type Class
        Rule* CreateRule(Type* type, const std::vector<Token*> tokens); // Used to create a Rule Class
        void  DeleteAllNodes();
        void  DeleteAllTypes();
        void  DeleteAllRules();
        void  PrintNodes();
        void  PrintTypes();
        void  PrintRules();
        void  SetLexer(LexerType_t lexerType);
        void  SetParser(ParserType_t parserType);
};

#endif //DEAMER_LANGUAGEGEN_LANGUAGEGEN_H