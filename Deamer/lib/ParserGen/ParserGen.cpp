/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#include "Deamer/ParserGen/ParserGen.h"
#include "Deamer/ParserGen/ParserFactory.h"
#include <sstream>

deamer::ParserGen::ParserGen(ParserType_t parserType_t, LanguageDefinition* langDef)
{
    ParserGen::langDef = langDef;
    ParserTarget = parserType_t;
    parserBuilder = ParserFactory().MakeParser(parserType_t, langDef);
}

void deamer::ParserGen::SetTarget(ParserType_t parserType_t)
{
    ParserTarget = parserType_t;
}

void deamer::ParserGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("Parser/");
    CreateDirectoryIfNotExist(dirTarget);

    parserBuilder->SetDirTarget(dirTarget);
    Directory = dirTarget;
}

void deamer::ParserGen::FileTarget(std::string fileTarget)
{
    parserBuilder->SetFileTarget(fileTarget);
}

void deamer::ParserGen::BuildNodes() const
{
    for(int i = langDef->Nodes.size() - 1; i >= 0; i--)
    {
        parserBuilder->AddNode(langDef->Nodes[i]);
    }
}

void deamer::ParserGen::BuildRulesOfType(Type* type) const
{
    for(int i = type->Rules.size() - 1; i >= 0; i--)
    {
        parserBuilder->AddRule(type->Rules[i]);
    }
}

void deamer::ParserGen::Build()
{
    BuildNodes();

    parserBuilder->StartBuild();

    for(int i = langDef->Types.size() - 1; i >= 0; i--)
    {
        parserBuilder->AddType(langDef->Types[i]);
        BuildRulesOfType(langDef->Types[i]);
    }
    parserBuilder->FinishBuild();
}

void deamer::ParserGen::Write()
{
    parserBuilder->SetFileTarget(langDef->LanguageName + Filename);
    parserBuilder->WriteOutputToFile();
}

std::string deamer::ParserGen::GetFileLocation() const
{
    std::ostringstream oss;
    oss << Directory << Filename;
    return oss.str();
}

std::string deamer::ParserGen::GetDirectoryLocation() const
{
    return Directory;
}
