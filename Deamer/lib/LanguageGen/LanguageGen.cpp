#include <iostream>
#include "Deamer/LanguageGen/LanguageGen.h"

LanguageGen::LanguageGen(LexerType_t lexerType, ParserType_t parserType, LanguageDefinition* languageDefinition)
{
    LanguageGen::languageDefinition = languageDefinition;
    LanguageGen::lexerGen = new LexerGen(lexerType, languageDefinition);
    LanguageGen::parserGen = new ParserGen(parserType, languageDefinition);
}


void LanguageGen::SetLexer(LexerType_t lexerType)
{
    LanguageGen::lexerGen->SetTarget(lexerType);
}

void LanguageGen::SetParser(ParserType_t parserType)
{
    LanguageGen::parserGen->SetTarget(parserType);
}

void LanguageGen::GenerateLexer()
{
    LanguageGen::lexerGen->BuildLexer();
}

void LanguageGen::GenerateParser()
{
    LanguageGen::parserGen->BuildParser();
}