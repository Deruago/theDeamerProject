/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
  */

#ifndef DEAMER_LANGUAGEGEN_LANGUAGEGEN_H
#define DEAMER_LANGUAGEGEN_LANGUAGEGEN_H

#include "Deamer/Types/Generator.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"
#include "Deamer/LexerGen/LexerGen.h"
#include "Deamer/ParserGen/ParserGen.h"
#include <string>

#include "Deamer/Types/SmartPointer/BaseAutoPtr.h"

/*
This header describes the class implementation of LanguageGen. Which is used to generate Types, Nodes and Rules
*/

namespace deamer
    {
    class LanguageGen : public Generator
    {
    private:
	    const LanguageDefinition& languageDefinition;
	    BaseAutoPtr<LexerGen> lexerGen;
        BaseAutoPtr<ParserGen> parserGen;
	    std::string Directory;

    public:
        LanguageGen(LexerType_t lexerType, ParserType_t parserType, const LanguageDefinition& languageDefinition);
        void CreateDefaultLexerAPI() const;      // Used to communicate with the lexer
        void CreateDefaultParserAPI() const;     // Used to communicate with the parser
        void CreateDefaultCompilerAPIHeader() const;   // Used to communicate with the compiler. The compiler API supports multiple interfaces/features.
        void CreateDefaultCompilerAPISource() const;   // Implements the API
	    void CreateDefaultCompilerSource() const;

	    void DirTarget(std::string dirTarget) override;
        void FileTarget(std::string fileTarget) override;
        void GenerateLexer() const;
        void GenerateParser() const;
        void SetLexer(LexerType_t lexerType) const;
        void SetParser(ParserType_t parserType) const;
        void Build() override;
        void Write() override;
        void Compile() const;
        bool DoesFileExist(const std::string& file_location) const;
        void Finish();
    };
}

#endif //DEAMER_LANGUAGEGEN_LANGUAGEGEN_H