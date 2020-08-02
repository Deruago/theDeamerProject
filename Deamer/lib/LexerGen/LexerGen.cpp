/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -June 2020 Thimo Bohmer
 * -July 2020 Thimo Bohmer
 */

#include "Deamer/LexerGen/LexerGen.h"
#include "Deamer/LexerGen/LexerFactory.h"
#include <sstream>

deamer::LexerGen::LexerGen(const LexerType_t LexerType_t, LanguageDefinition* langDef)
{
    LexerGen::langDef = langDef;
    LexerTarget = LexerType_t;
    lexerBuilder = LexerFactory().MakeLexerUseRecursiveBasedDS(LexerType_t, langDef);
}

void deamer::LexerGen::SetTarget(LexerType_t LexerType_t)
{
    LexerTarget = LexerType_t;
}

void deamer::LexerGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("Lexer/");
    CreateDirectoryIfNotExist(&dirTarget);
    
    lexerBuilder->SetDirTarget(dirTarget);
    Directory = dirTarget;
}

void deamer::LexerGen::FileTarget(std::string fileTarget)
{
    lexerBuilder->SetFileTarget(fileTarget);
}

bool deamer::LexerGen::Build()
{
    lexerBuilder->StartBuild();
    for (auto& Node : langDef->Nodes)
    {
        lexerBuilder->AddNode(Node);
    }
    
    for (auto& IgnoreNode : langDef->IgnoreNodes)
    {
        lexerBuilder->AddIgnoreNode(IgnoreNode);
    }

    bool IsBuildSuccesfull = lexerBuilder->FinishBuild();
    //std::cout << deamer::LexerGen::lexerBuilder->GetOutput() << "\n";
    return IsBuildSuccesfull;
}

bool deamer::LexerGen::Write()
{
    lexerBuilder->SetFileTarget(langDef->LanguageName + Filename);
    lexerBuilder->WriteOutputToFile();

    return true;
}

std::string deamer::LexerGen::GetFileLocation() const
{
    std::ostringstream oss;
    oss << Directory << Filename;
    return oss.str();
}

std::string deamer::LexerGen::GetDirectoryLocation() const
{
    return Directory;
}
