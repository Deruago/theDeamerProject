/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/LexerGen/LexerGen.h"
#include <sstream>
#include <iostream>
#include <fstream>

deamer::LexerBuilder* deamer::LexerGen::GetBuilder(deamer::LexerType_t LexerType_t)
{
    switch(LexerType_t)
    {
        case LexerType_t::dlex:
            return new DlexBuilder(deamer::LexerGen::langDef);
        case LexerType_t::flex:
            return new FlexBuilder(deamer::LexerGen::langDef);
    }
    return nullptr;
}

deamer::LexerGen::LexerGen(LexerType_t LexerType_t, LanguageDefinition* langDef)
{
    deamer::LexerGen::langDef = langDef;
    deamer::LexerGen::LexerTarget = LexerType_t;
    deamer::LexerGen::lexerBuilder = deamer::LexerGen::GetBuilder(deamer::LexerGen::LexerTarget);
}

void deamer::LexerGen::SetTarget(LexerType_t LexerType_t)
{
    deamer::LexerGen::LexerTarget = LexerType_t;
}

void deamer::LexerGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("Lexer/");
    deamer::LexerGen::CreateDirectoryIfNotExist(&dirTarget);
    
    deamer::LexerGen::lexerBuilder->SetDirTarget(dirTarget);
    deamer::LexerGen::Directory = dirTarget;
}

void deamer::LexerGen::FileTarget(std::string fileTarget)
{
    deamer::LexerGen::lexerBuilder->SetFileTarget(fileTarget);
}

bool deamer::LexerGen::Build()
{
    if(deamer::LexerGen::lexerBuilder == nullptr)
    {
        deamer::LexerGen::lexerBuilder = GetBuilder(deamer::LexerGen::LexerTarget);
    }
    
    deamer::LexerGen::lexerBuilder->StartBuild();
    for(int i = 0; i < deamer::LexerGen::langDef->Nodes.size(); i++)
    {
        deamer::LexerGen::lexerBuilder->AddNode(deamer::LexerGen::langDef->Nodes[i]);
    }

    bool IsBuildSuccesfull = deamer::LexerGen::lexerBuilder->FinishBuild();
    //std::cout << deamer::LexerGen::lexerBuilder->GetOutput() << "\n";
    return IsBuildSuccesfull;
}

bool deamer::LexerGen::Write()
{
    deamer::LexerGen::lexerBuilder->SetFileTarget(deamer::LexerGen::langDef->GetLanguageName() + deamer::LexerGen::Filename);
    deamer::LexerGen::lexerBuilder->WriteOutputToFile();

    return true;
}

std::string deamer::LexerGen::GetFileLocation()
{
    std::ostringstream oss;
    oss << deamer::LexerGen::Directory << deamer::LexerGen::Filename;
    return oss.str();
}

std::string deamer::LexerGen::GetDirectoryLocation()
{
    return deamer::LexerGen::Directory;
}