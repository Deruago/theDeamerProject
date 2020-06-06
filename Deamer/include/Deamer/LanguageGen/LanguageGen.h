#ifndef DEAMER_LANGUAGEGEN_LANGUAGEGEN_H
#define DEAMER_LANGUAGEGEN_LANGUAGEGEN_H

#include "Deamer/Deamer.h"
#include "Deamer/Types/Generator.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/Node.h"
#include "Deamer/LanguageGen/Type.h"
#include "Deamer/LanguageGen/Token.h"
#include "Deamer/LanguageGen/Rule.h"
#include "Deamer/LexerGen/LexerGen.h"
#include "Deamer/ParserGen/ParserGen.h"
#include <string>
#include <vector>

/*
This header describes the class implementation of LanguageGen. Which is used to generate Types, Nodes and Rules
*/
using namespace Deamer;

class LanguageGen : public Generator
{
    LanguageDefinition* languageDefinition;
    LexerGen* lexerGen;
    ParserGen* parserGen;

    public:
        LanguageGen(LexerType_t lexerType, ParserType_t parserType, LanguageDefinition* languageDefinition);
        void DirTarget(std::string dirTarget) override;
        void GenerateLexer();
        void GenerateParser();
        void SetLexer(LexerType_t lexerType);
        void SetParser(ParserType_t parserType);
        bool Build() override;
};

#endif //DEAMER_LANGUAGEGEN_LANGUAGEGEN_H