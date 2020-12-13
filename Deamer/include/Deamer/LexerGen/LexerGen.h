/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -June 2020 Thimo B�hmer
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_LEXERGEN_LEXERGEN_G
#define DEAMER_LEXERGEN_LEXERGEN_G

#include "Deamer/Types/Generator.h"
#include "Deamer/LexerGen/LexerBuilder.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/Types/SmartPointer/BaseAutoPtr.h"
#include <string>

namespace deamer
{
    class LexerGen : public Generator
    {
    private:
        std::string Directory;
        std::string Filename = "lexer.l";

        LexerType_t LexerTarget;
    	LanguageDefinition* langDef;
        BaseAutoPtr<LexerBuilder> lexerBuilder;
    public:
        LexerGen(LexerType_t LexerTarget, LanguageDefinition* languageDefinition);
        virtual ~LexerGen() = default;
    	
    	std::string GetFileLocation() const;
        std::string GetDirectoryLocation() const;

    	void DirTarget(std::string dirTarget) override;
        void FileTarget(std::string fileTarget) override;
        void SetTarget(LexerType_t LexerTarget);
        void Build() override;
        void Write() override;
    };
}

#endif //DEAMER_LEXERGEN_LEXERGEN_G