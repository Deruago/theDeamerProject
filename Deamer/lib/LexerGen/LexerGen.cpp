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

deamer::LexerGen::LexerGen(const LexerType_t LexerTarget, const LanguageDefinition* languageDefinition)
		:   LexerTarget(LexerTarget),
			langDef(languageDefinition),
			lexerBuilder(LexerFactory().MakeLexerUseRecursiveBasedDS(LexerTarget, languageDefinition))
{
}

void deamer::LexerGen::SetTarget(LexerType_t LexerType_t)
{
    LexerTarget = LexerType_t;
}

void deamer::LexerGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("Lexer/");
    CreateDirectoryIfNotExist(dirTarget);
    
    lexerBuilder->SetDirTarget(dirTarget);
    Directory = dirTarget;
}

void deamer::LexerGen::FileTarget(std::string fileTarget)
{
    lexerBuilder->SetFileTarget(fileTarget);
}

void deamer::LexerGen::Build()
{
    lexerBuilder->StartBuild();
    for (const auto& Node : langDef->GetNodes())
    {
        if (Node->TokenPermission.has_flag(TokenPermission_t::delete_))
        {
            lexerBuilder->AddDeleteNode(Node);
        }
        else if (Node->TokenPermission.has_flag(TokenPermission_t::ignore))
        {
            lexerBuilder->AddIgnoreNode(Node);
        }
        else
        {
            lexerBuilder->AddNode(Node);
        }
    }
    
    for (const auto& IgnoreNode : langDef->GetIgnoreNodes())
    {
        lexerBuilder->AddIgnoreNode(IgnoreNode);
    }

    lexerBuilder->FinishBuild();
}

void deamer::LexerGen::Write()
{
    lexerBuilder->SetFileTarget(langDef->LanguageName + Filename);
    lexerBuilder->WriteOutputToFile();
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
