#include <iostream>
#include "Deamer/LexerGen/LexerGen.h"

LexerGen::LexerGen(LexerType_t LexerType_t, LanguageDefinition* langDef)
{
    LexerGen::LexerTarget = LexerType_t;
    LexerGen::langDef = langDef;
}

void LexerGen::SetTarget(LexerType_t LexerType_t)
{
    LexerGen::LexerTarget = LexerType_t;
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

bool LexerGen::BuildLexer()
{
    LexerGen::LexerBuilder = GetBuilder(LexerGen::LexerTarget);
    
    LexerGen::LexerBuilder->StartBuild();
    for(int i = 0; i < LexerGen::langDef->Nodes.size(); i++)
    {
        LexerGen::LexerBuilder->AddNode(LexerGen::langDef->Nodes[i]);
    }

    bool IsBuildSuccesfull = LexerGen::LexerBuilder->FinishBuild();
    std::cout << LexerGen::LexerBuilder->GetOutput() << "\n";
    return IsBuildSuccesfull;
}
