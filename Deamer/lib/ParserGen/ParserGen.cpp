#include "Deamer/ParserGen/ParserGen.h"

ParserGen::ParserGen(ParserType_t parserType_t, LanguageDefinition* langDef)
{
    ParserGen::ParserTarget = parserType_t;
    ParserGen::langDef = langDef;
}

void ParserGen::SetTarget(ParserType_t parserType_t)
{
    ParserGen::ParserTarget = parserType_t;
}

static ParserBuilder* GetBuilder(ParserType_t parserType_t)
{
    switch(parserType_t)
    {
        case ParserType_t::dparse:
            return new DParseBuilder();
        case ParserType_t::bison:
            return new BisonBuilder();
    }
}

void ParserGen::BuildNodes()
{
    for(int i = langDef->Nodes.size() - 1; i >= 0; i--)
    {
        ParserGen::parserBuilder->AddNode(langDef->Nodes[i]);
    }
}

void ParserGen::BuildRulesOfType(Type* type)
{
    for(int i = type->Rules.size() - 1; i >= 0; i--)
    {
        ParserGen::parserBuilder->AddRule(type->Rules[i]);
    }
}

bool ParserGen::BuildParser()
{
    ParserGen::parserBuilder = GetBuilder(ParserGen::ParserTarget);

    ParserGen::BuildNodes();

    for(int i = langDef->Types.size() - 1; i >= 0; i--)
    {
        ParserGen::parserBuilder->AddType(langDef->Types[i]);
        BuildRulesOfType(langDef->Types[i]);
    }
    return ParserGen::parserBuilder->FinishBuild();
}