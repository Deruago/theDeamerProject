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

#include "Deamer/LexerGen/LexerGen.h"
#include "Deamer/LexerGen/LexerFactory.h"
#include <sstream>

deamer::LexerGen::LexerGen(const LexerType_t LexerTarget, const LanguageDefinition* languageDefinition)
		:   LexerTarget(LexerTarget),
			langDef(languageDefinition),
			lexerBuilder(LexerFactory().MakeLexerUseRecursiveBasedDS(LexerTarget, languageDefinition))
{
}

void deamer::LexerGen::SetTarget(LexerType_t LexerType_t)
{
    LexerTarget = LexerType_t;
}

void deamer::LexerGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("Lexer/");
    CreateDirectoryIfNotExist(dirTarget);
    
    lexerBuilder->SetDirTarget(dirTarget);
    Directory = dirTarget;
}

void deamer::LexerGen::FileTarget(std::string fileTarget)
{
    lexerBuilder->SetFileTarget(fileTarget);
}

void deamer::LexerGen::Build()
{
    lexerBuilder->StartBuild();
    for (const auto& Node : langDef->GetNodes())
    {
        if (Node->TokenPermission.has_flag(TokenPermission_t::delete_))
        {
            lexerBuilder->AddDeleteNode(Node);
        }
        else if (Node->TokenPermission.has_flag(TokenPermission_t::ignore))
        {
            lexerBuilder->AddIgnoreNode(Node);
        }
        else
        {
            lexerBuilder->AddNode(Node);
        }
    }
    
    for (const auto& IgnoreNode : langDef->GetIgnoreNodes())
    {
        lexerBuilder->AddIgnoreNode(IgnoreNode);
    }

    lexerBuilder->FinishBuild();
}

void deamer::LexerGen::Write()
{
    lexerBuilder->SetFileTarget(langDef->LanguageName + Filename);
    lexerBuilder->WriteOutputToFile();
}

std::string deamer::LexerGen::GetFileLocation() const
{
    std::ostringstream oss;
    oss << Directory << Filename;
    return oss.str();
}

std::string deamer::LexerGen::GetDirectoryLocation() const
{
    return Directory;
}
