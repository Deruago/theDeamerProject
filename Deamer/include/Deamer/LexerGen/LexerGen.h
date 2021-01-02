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
    	const LanguageDefinition* langDef;
        BaseAutoPtr<LexerBuilder> lexerBuilder;
    public:
        LexerGen(LexerType_t LexerTarget, const LanguageDefinition* languageDefinition);
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