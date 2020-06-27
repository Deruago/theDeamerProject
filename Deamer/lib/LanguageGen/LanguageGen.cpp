#include "Deamer/LanguageGen/LanguageGen.h"
#include <iostream>
#include <sstream>

LanguageGen::LanguageGen(LexerType_t lexerType, ParserType_t parserType, LanguageDefinition* languageDefinition)
{
    LanguageGen::languageDefinition = languageDefinition;
    LanguageGen::lexerGen = new LexerGen(lexerType, languageDefinition);
    LanguageGen::parserGen = new ParserGen(parserType, languageDefinition);
}

void LanguageGen::DirTarget(std::string TargetDir)
{
    LanguageGen::lexerGen->DirTarget(TargetDir);
    LanguageGen::parserGen->DirTarget(TargetDir);
}

void LanguageGen::FileTarget(std::string fileTarget)
{
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
    LanguageGen::lexerGen->Build();
}

void LanguageGen::GenerateParser()
{
    LanguageGen::parserGen->Build();
}

bool LanguageGen::Build()
{
    bool buildIsSuccesfull;
    buildIsSuccesfull = LanguageGen::lexerGen->Build();
    if (!buildIsSuccesfull)
    {
        return buildIsSuccesfull;
    }

    buildIsSuccesfull = LanguageGen::parserGen->Build();
    return buildIsSuccesfull;
}

bool LanguageGen::Write()
{
    LanguageGen::lexerGen->Write();
    LanguageGen::parserGen->Write();

    return true;
}

bool LanguageGen::Compile()
{
    /*Currently only supports Flex and Bison (c++ variant)*/
    std::ostringstream ossLexer;
    ossLexer << "flex " << LanguageGen::lexerGen->GetFileLocation();
    std::system(ossLexer.str().c_str());

    std::ostringstream ossParser;
    ossParser << "bison -d " << LanguageGen::parserGen->GetFileLocation();
    std::system(ossParser.str().c_str());

    std::system("g++ parser.tab.c lex.yy.c -lfl -o Parser.out");

    return true;
}

bool LanguageGen::Finish()
{
    LanguageGen::GenerateLexer();
    LanguageGen::GenerateParser();

    if(!LanguageGen::Build())
    {
        return false;
    }

    if(!LanguageGen::Write())
    {
        return false;
    }

    if(!LanguageGen::Compile())
    {
        return false;
    }

    return true;
}