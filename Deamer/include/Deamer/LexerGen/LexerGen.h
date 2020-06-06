#ifndef DEAMER_LEXERGEN_LEXERGEN_G
#define DEAMER_LEXERGEN_LEXERGEN_G

#include "Deamer/Types/Generator.h"
#include "Deamer/LexerGen/LexerBuilder.h"
#include "Deamer/LexerGen/FlexBuilder.h"
#include "Deamer/LexerGen/DlexBuilder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

class LexerGen : public Generator
{
    LexerBuilder* lexerBuilder;
    LexerType_t LexerTarget;
    LanguageDefinition* langDef;
    void SetLexerBuilder();
    public:
        LexerGen(LexerType_t LexerTarget, LanguageDefinition* langDef);
        void DirTarget(std::string dirTarget) override;
        void SetTarget(LexerType_t LexerTarget);
        bool BuildLexer();
        void SetLangDef(LanguageDefinition* langDef);
};

#endif //DEAMER_LEXERGEN_LEXERGEN_G