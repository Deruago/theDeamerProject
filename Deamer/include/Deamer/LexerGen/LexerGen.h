/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LEXERGEN_LEXERGEN_G
#define DEAMER_LEXERGEN_LEXERGEN_G

#include "Deamer/Types/Generator.h"
#include "Deamer/LexerGen/LexerBuilder.h"
#include "Deamer/LexerGen/FlexBuilder.h"
#include "Deamer/LexerGen/DlexBuilder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include <string>

namespace deamer
{
    class LexerGen : public Generator
    {
        private:
            LexerBuilder* GetBuilder(LexerType_t LexerType_t);
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
}

#endif //DEAMER_LEXERGEN_LEXERGEN_G