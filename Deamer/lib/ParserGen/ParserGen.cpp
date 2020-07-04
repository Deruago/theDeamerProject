#include "Deamer/ParserGen/ParserGen.h"
#include <sstream>
#include <iostream>
#include <fstream>

deamer::ParserBuilder* deamer::ParserGen::GetBuilder(deamer::ParserType_t parserType_t)
{
    switch(parserType_t)
    {
        case ParserType_t::dparse:
            return new DParseBuilder(deamer::ParserGen::langDef);
        case ParserType_t::bison:
            return new BisonBuilder(deamer::ParserGen::langDef);
    }
    return nullptr;
}

deamer::ParserGen::ParserGen(deamer::ParserType_t parserType_t, deamer::LanguageDefinition* langDef)
{
    deamer::ParserGen::langDef = langDef;
    deamer::ParserGen::ParserTarget = parserType_t;
    deamer::ParserGen::parserBuilder = deamer::ParserGen::GetBuilder(deamer::ParserGen::ParserTarget);
}

void deamer::ParserGen::SetTarget(deamer::ParserType_t parserType_t)
{
    deamer::ParserGen::ParserTarget = parserType_t;
}

void deamer::ParserGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("Parser/");
    deamer::ParserGen::CreateDirectoryIfNotExist(&dirTarget);

    deamer::ParserGen::parserBuilder->SetDirTarget(dirTarget);
    deamer::ParserGen::Directory = dirTarget;
}

void deamer::ParserGen::FileTarget(std::string fileTarget)
{
    deamer::ParserGen::parserBuilder->SetFileTarget(fileTarget);
}

void deamer::ParserGen::BuildNodes()
{
    for(int i = langDef->Nodes.size() - 1; i >= 0; i--)
    {
        deamer::ParserGen::parserBuilder->AddNode(langDef->Nodes[i]);
    }
}

void deamer::ParserGen::BuildRulesOfType(Type* type)
{
    for(int i = type->Rules.size() - 1; i >= 0; i--)
    {
        deamer::ParserGen::parserBuilder->AddRule(type->Rules[i]);
    }
}

bool deamer::ParserGen::Build()
{
    if (deamer::ParserGen::parserBuilder == nullptr)
    {
        deamer::ParserGen::parserBuilder = GetBuilder(deamer::ParserGen::ParserTarget);
    }

    deamer::ParserGen::BuildNodes();

    deamer::ParserGen::parserBuilder->StartBuild();

    for(int i = langDef->Types.size() - 1; i >= 0; i--)
    {
        deamer::ParserGen::parserBuilder->AddType(langDef->Types[i]);
        BuildRulesOfType(langDef->Types[i]);
    }
    bool BuildSuccessfull = deamer::ParserGen::parserBuilder->FinishBuild();
    //std::cout << deamer::ParserGen::parserBuilder->GetOutput() << "\n";
    return BuildSuccessfull;
}

bool deamer::ParserGen::Write()
{
    deamer::ParserGen::parserBuilder->SetFileTarget(deamer::ParserGen::langDef->GetLanguageName() + deamer::ParserGen::Filename);
    deamer::ParserGen::parserBuilder->WriteOutputToFile();

    return true;
}

std::string deamer::ParserGen::GetFileLocation()
{
    std::ostringstream oss;
    oss << deamer::ParserGen::Directory << deamer::ParserGen::Filename;
    return oss.str();
}

std::string deamer::ParserGen::GetDirectoryLocation()
{
    return deamer::ParserGen::Directory;
}