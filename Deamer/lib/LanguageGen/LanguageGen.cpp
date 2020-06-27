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

    std::ostringstream ossLexerReplace;
    ossLexerReplace << "mv lex.yy.c " << LanguageGen::lexerGen->GetDirectoryLocation() << "lex.yy.c";
    std::system(ossLexerReplace.str().c_str());

    std::ostringstream ossParser;
    ossParser << "bison -d " << LanguageGen::parserGen->GetFileLocation();
    std::system(ossParser.str().c_str());

    std::ostringstream ossCompileLexer;
    ossCompileLexer << "g++ -c " << LanguageGen::lexerGen->GetDirectoryLocation() << "lex.yy.c" << " -lfl -o" << LanguageGen::lexerGen->GetDirectoryLocation() << "lex.yy.o";
    std::system(ossCompileLexer.str().c_str());

    std::ostringstream ossCompileParser;
    ossCompileParser << "g++ -c "  << LanguageGen::parserGen->GetDirectoryLocation() << "parser.tab.c -lfl -o" << LanguageGen::parserGen->GetDirectoryLocation() << "parser.tab.o";
    std::system(ossCompileParser.str().c_str());
    
    return true;
}

bool LanguageGen::Finish()
{
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