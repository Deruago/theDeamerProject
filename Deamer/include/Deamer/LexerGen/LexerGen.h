#ifndef DEAMER_LEXERGEN_LEXERGEN_G
#define DEAMER_LEXERGEN_LEXERGEN_G

#include "Deamer/Types/Generator.h"
#include "Deamer/LexerGen/LexerBuilder.h"
#include "Deamer/LexerGen/FlexBuilder.h"
#include "Deamer/LexerGen/DlexBuilder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <string>

class LexerGen : public Generator
{
    LexerBuilder* lexerBuilder;
    LanguageDefinition* langDef;
    std::string Directory;
    std::string Filename = "lexer.l";
    void SetLexerBuilder();
    public:
        LexerType_t LexerTarget;
        std::string GetFileLocation();
        std::string GetDirectoryLocation();
        LexerGen(LexerType_t LexerTarget, LanguageDefinition* langDef);
        void DirTarget(std::string dirTarget) override;
        void FileTarget(std::string fileTarget) override;
        void SetTarget(LexerType_t LexerTarget);
        bool Build() override;
        bool Write() override;
        void SetLangDef(LanguageDefinition* langDef);
};

#endif //DEAMER_LEXERGEN_LEXERGEN_G