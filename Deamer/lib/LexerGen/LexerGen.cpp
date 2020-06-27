#include "Deamer/LexerGen/LexerGen.h"
#include <sstream>
#include <iostream>
#include <fstream>

LexerGen::LexerGen(LexerType_t LexerType_t, LanguageDefinition* langDef)
{
    LexerGen::LexerTarget = LexerType_t;
    LexerGen::langDef = langDef;
}

void LexerGen::SetTarget(LexerType_t LexerType_t)
{
    LexerGen::LexerTarget = LexerType_t;
}

void LexerGen::DirTarget(std::string dirTarget)
{
    LexerGen::lexerBuilder->SetDirTarget(dirTarget + "Lexer/");
}

void LexerGen::FileTarget(std::string fileTarget)
{
    LexerGen::lexerBuilder->SetFileTarget(fileTarget);
}

static LexerBuilder* GetBuilder(LexerType_t LexerType_t)
{
    switch(LexerType_t)
    {
        case LexerType_t::dlex:
            return new DlexBuilder();
        case LexerType_t::flex:
            return new FlexBuilder();
    }
}

bool LexerGen::Build()
{
    LexerGen::lexerBuilder = GetBuilder(LexerGen::LexerTarget);
    
    LexerGen::lexerBuilder->StartBuild();
    for(int i = 0; i < LexerGen::langDef->Nodes.size(); i++)
    {
        LexerGen::lexerBuilder->AddNode(LexerGen::langDef->Nodes[i]);
    }

    bool IsBuildSuccesfull = LexerGen::lexerBuilder->FinishBuild();
    std::cout << LexerGen::lexerBuilder->GetOutput() << "\n";
    return IsBuildSuccesfull;
}

bool LexerGen::Write()
{
    LexerGen::lexerBuilder->SetFileTarget(LexerGen::Filename);
    LexerGen::lexerBuilder->WriteOutputToFile();

    return true;
}

std::string LexerGen::GetFileLocation()
{
    std::ostringstream oss;
    oss << LexerGen::Directory << LexerGen::Filename;
    return oss.str();
}