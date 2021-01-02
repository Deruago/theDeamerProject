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

#include "Deamer/ParserGen/ParserGen.h"
#include "Deamer/ParserGen/ParserFactory.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include <sstream>

deamer::ParserGen::ParserGen(ParserType_t parserType_t, const LanguageDefinition* langDef)
		:   ParserTarget(parserType_t),
			langDef(langDef),
			parserBuilder(ParserFactory().MakeParser(parserType_t, langDef))
{
}

void deamer::ParserGen::SetTarget(ParserType_t parserType_t)
{
    ParserTarget = parserType_t;
}

void deamer::ParserGen::DirTarget(std::string dirTarget)
{
    dirTarget.append("Parser/");
    CreateDirectoryIfNotExist(dirTarget);

    parserBuilder->SetDirTarget(dirTarget);
    Directory = dirTarget;
}

void deamer::ParserGen::FileTarget(std::string fileTarget)
{
    parserBuilder->SetFileTarget(fileTarget);
}

void deamer::ParserGen::BuildNodes() const
{
	for(Node* node : langDef->GetNodes())
	{
        parserBuilder->AddNode(node);
	}
}

void deamer::ParserGen::Build()
{
    BuildNodes();

    parserBuilder->StartBuild();

	for(Type* type : langDef->GetTypes())
        parserBuilder->AddType(type);
	
    parserBuilder->FinishBuild();
}

void deamer::ParserGen::Write()
{
    parserBuilder->SetFileTarget(langDef->LanguageName + Filename);
    parserBuilder->WriteOutputToFile();
}

std::string deamer::ParserGen::GetFileLocation() const
{
    std::ostringstream oss;
    oss << Directory << Filename;
    return oss.str();
}

std::string deamer::ParserGen::GetDirectoryLocation() const
{
    return Directory;
}
