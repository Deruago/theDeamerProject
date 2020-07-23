/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEGEN_LANGUAGEGEN_H
#define DEAMER_LANGUAGEGEN_LANGUAGEGEN_H

#include "Deamer/Types/Generator.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LexerGen/LexerGen.h"
#include "Deamer/ParserGen/ParserGen.h"
#include <string>

/*
This header describes the class implementation of LanguageGen. Which is used to generate Types, Nodes and Rules
*/

namespace deamer
    {
    class LanguageGen : public Generator
    {
        LanguageDefinition* languageDefinition;
        LexerGen* lexerGen;
        ParserGen* parserGen;
        std::string Directory;

        public:
            LanguageGen(LexerType_t lexerType, ParserType_t parserType, LanguageDefinition* languageDefinition);
            bool CreateDefaultLexerAPI() const;      // Used to communicate with the lexer
            bool CreateDefaultParserAPI() const;     // Used to communicate with the parser
            bool CreateDefaultCompilerAPIHeader() const;   // Used to communicate with the compiler. The compiler API supports multiple interfaces/features.
            bool CreateDefaultCompilerAPISource() const;   // Implements the API
            void DirTarget(std::string dirTarget) override;
            void FileTarget(std::string fileTarget) override;
            void GenerateLexer() const;
            void GenerateParser() const;
            void SetLexer(LexerType_t lexerType) const;
            void SetParser(ParserType_t parserType) const;
            bool Build() override;
            bool Write() override;
            bool Compile() const;
            bool Finish();
    };
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEGEN_H