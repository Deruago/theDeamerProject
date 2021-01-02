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

#include "Deamer/FileBuilder/Types/FileHeaderSection.h"
#include "Deamer/FileBuilder/Types/FileHeaderGuardSection.h"
#include "Deamer/FileBuilder/Types/FileClassSection.h"
#include "Deamer/FileBuilder/Types/FileNamespaceSection.h"
#include "Deamer/FileBuilder/Types/FileFunctionPrototypeSection.h"
#include "Deamer/FileBuilder/Types/FileFunctionSection.h"
#include "Deamer/StringBuilder/StringBuilder.h"
#include <vector>
#include <string>

#include "Deamer/FileBuilder/Types/FileIncludeSection.h"

deamer::FileHeaderSection::FileHeaderSection(Directory* dir, File* file) : FileSection(dir, file)
{
	headerGuard = AddHeaderGuard(GetDirectory(), GetFile());
}

deamer::FileHeaderSection::~FileHeaderSection()
{
	delete_members(includes);
	delete_members(classes);
	delete_members(functions);
}


deamer::FileHeaderGuardSection* deamer::FileHeaderSection::AddHeaderGuard(Directory* directory, File* file)
{
	return new FileHeaderGuardSection(directory, file);
}

std::string deamer::FileHeaderSection::GetOutput()
{
	StringBuilder headerFile;
	headerFile.Add(headerGuard->GetHeaderGuardBegin());
	for(FileIncludeSection* include : includes)
	{
		headerFile.Add(include->GetOutput());
	}
	if(!includes.empty())
		headerFile.Add();
	
	for(FileSection* file_section : FileSections)
	{
		headerFile.Add(file_section->GetOutput());
	}
	
	headerFile.Add(headerGuard->GetHeaderGuardEnd());
	return headerFile.GetOutput();
}

void deamer::FileHeaderSection::AddInclude(const std::string& cs, bool isSystem)
{
	includes.push_back(new FileIncludeSection(cs, isSystem));
}

deamer::FileNamespaceSection* deamer::FileHeaderSection::AddNamespace(std::string namespaceName)
{
	const auto newNamespace = new FileNamespaceSection(namespaceName);
	AddSection(newNamespace);
	return newNamespace;
}

deamer::FileClassSection* deamer::FileHeaderSection::AddClass(std::string className,
	std::vector<FileClassSection*> superClasses, FileNamespaceSection* scope)
{
	const auto newClass = new FileClassSection(className, superClasses, scope);
	AddSection(newClass);
	return newClass;
}

void deamer::FileHeaderSection::AddClass(FileClassSection* classSection)
{
	AddSection(classSection);
}

deamer::FileFunctionSection* deamer::FileHeaderSection::AddFunction(std::string functionName,
                                                                    std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope)
{
	return AddFunction(new FileFunctionPrototypeSection(functionName, functionArgs, returnType, scope));
}

deamer::FileFunctionSection* deamer::FileHeaderSection::AddFunction(FileFunctionPrototypeSection* functionPrototype)
{
	auto newFunction = new FileFunctionSection(functionPrototype);
	AddSection(newFunction);
	return newFunction;
}