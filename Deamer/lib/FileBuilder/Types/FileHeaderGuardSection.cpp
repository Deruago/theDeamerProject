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

#include "Deamer/FileBuilder/Types/FileHeaderGuardSection.h"
#include "Deamer/FileBuilder/Directory.h"
#include "Deamer/FileBuilder/File.h"
#include "Deamer/StringBuilder/StringBuilder.h"
#include <string>

deamer::FileHeaderGuardSection::FileHeaderGuardSection(Directory* directory, File* file) : FileSection(directory, file)
{
	SetHeaderGuardBegin(directory, file);
	SetHeaderGuardEnd(directory, file);
}

std::string deamer::FileHeaderGuardSection::GetHeaderGuardBegin() const
{
	return HeaderGuardBegin;
}

std::string deamer::FileHeaderGuardSection::GetHeaderGuardEnd() const
{
	return HeaderGuardEnd;
}

void deamer::FileHeaderGuardSection::AddFileToHeaderGuardMacro(StringBuilder* string, const File* file)
{
	string->AddUpper(file->GetFileName());
	string->Add("_");
	string->AddUpper(file->GetFileExtension());
}

void deamer::FileHeaderGuardSection::AddDirectoryToHeaderGuardMacro(StringBuilder* string,
	const  Directory* directory)
{
	for(std::string curDirectory : directory->GetDirectoryFullPath())
	{
		string->AddUpper(curDirectory);
		string->Add("_");
	}
}

std::string deamer::FileHeaderGuardSection::GetHeaderGuardMacro(const deamer::Directory* directory, const deamer::File* file)
{
	StringBuilder macroDefinition;
	AddDirectoryToHeaderGuardMacro(&macroDefinition, directory);
	AddFileToHeaderGuardMacro(&macroDefinition, file);
	return macroDefinition.GetOutputIgnoreNewLine();
}

std::string deamer::FileHeaderGuardSection::GetHeaderGuardMacroDefinition(const Directory* directory, const File* file)
{
	StringBuilder defineMacro;
	defineMacro.Add("#define ");
	defineMacro.Add(GetHeaderGuardMacro(directory, file));
	return defineMacro.GetOutputIgnoreNewLine();
}

std::string deamer::FileHeaderGuardSection::GetHeaderGuardMacroIfNotDefinedCheck(const  Directory* directory,
                                                                                 const File* file)
{
	StringBuilder macroLogic;
	macroLogic.Add("#ifndef ");
	macroLogic.Add(GetHeaderGuardMacro(directory, file));
	return macroLogic.GetOutputIgnoreNewLine();
}

void deamer::FileHeaderGuardSection::SetHeaderGuardBegin(const Directory* directory, const File* file)
{
	StringBuilder headerGuardBegin = StringBuilder();
	headerGuardBegin.Add(GetHeaderGuardMacroIfNotDefinedCheck(directory, file));
	headerGuardBegin.Add(GetHeaderGuardMacroDefinition(directory, file));
	HeaderGuardBegin = headerGuardBegin.GetOutput();
}

void deamer::FileHeaderGuardSection::SetHeaderGuardEnd(const Directory* directory, const File* file)
{
	StringBuilder headerGuardEnd = StringBuilder();
	headerGuardEnd.Add("#endif //");
	headerGuardEnd.Add(GetHeaderGuardMacro(directory, file));
	HeaderGuardEnd = headerGuardEnd.GetOutputIgnoreNewLine();
}

std::string deamer::FileHeaderGuardSection::GetOutput()
{
	return "";
}
