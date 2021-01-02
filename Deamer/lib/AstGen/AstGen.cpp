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

#include "Deamer/AstGen/AstGen.h"
#include "Deamer/AstGen/AstBuilderFactory.h"
#include <sstream>

deamer::AstGen::AstGen(const LanguageDefinition& language_definition, AstBuilderType ast_builder_type) : language_definition_(language_definition)
{
    astBuilder = AstBuilderFactory().MakeAstBuilder(ast_builder_type, "AstNodes/", language_definition_.LanguageName);
    CreateDirectoryIfNotExist("AstNodes/");
}

//deamer::AstGen::AstGen(std::string dirTarget)
//{
//    AstGen::DirTarget(dirTarget);
//}

void deamer::AstGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("AstNodes/");
}

void deamer::AstGen::FileTarget(std::string fileTarget)
{
}

void deamer::AstGen::CreateAstNodes()
{
    astBuilder->StartBuild();
    for (const auto& Type : language_definition_.GetTypes())
    {
        if (!Type->TokenPermission.has_flag(TokenPermission_t::ignore))
            astBuilder->Build(*Type);
    }
	
    for (const auto& Node : language_definition_.GetNodes())
    {
        if (!Node->TokenPermission.has_flag(TokenPermission_t::ignore))
            astBuilder->Build(*Node);
    }
    astBuilder->FinishBuild();
}