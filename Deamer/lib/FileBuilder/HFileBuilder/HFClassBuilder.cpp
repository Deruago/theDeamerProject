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

#include "Deamer/FileBuilder/HFileBuilder/HFClassBuilder.h"
#include "Deamer/FileBuilder/Types/FileClassSection.h"
#include "Deamer/FileBuilder/Directory.h"
#include "Deamer/FileBuilder/File.h"
#include "Deamer/FileBuilder/Types/FileFunctionSection.h"
#include "Deamer/FileBuilder/Types/FileHeaderSection.h"


deamer::HFClassBuilder::HFClassBuilder(Directory* directory, File* file, FileNamespaceSection* scope, std::vector<FileClassSection*> superClasses) : FileBuilder(directory, file)
{
	headerSection = new FileHeaderSection(_Directory, _File);
	_class = new FileClassSection(_File->GetFileName(), superClasses, scope);
	headerSection->AddClass(_class);
}

deamer::HFClassBuilder::HFClassBuilder(std::vector<std::string> directories, std::string fileName,
	FileNamespaceSection* scope, std::vector<FileClassSection*> superClasses) : HFClassBuilder(new Directory(directories), new File(fileName, "h"), scope, superClasses)
{
}

deamer::HFClassBuilder::HFClassBuilder(std::vector<std::string> directories, std::string fileName,
                                       FileNamespaceSection* scope) : HFClassBuilder(new Directory(directories), new File(fileName, "h"), scope, {})
{
}

deamer::HFClassBuilder::HFClassBuilder(std::vector<std::string> directories, std::string fileName) : HFClassBuilder(new Directory(directories), new File(fileName, "h"), nullptr, {})
{
}

deamer::HFClassBuilder::~HFClassBuilder()
{
	delete headerSection;
}

void deamer::HFClassBuilder::AddInclude(std::string include) const
{
	AddInclude(include, false);
}

void deamer::HFClassBuilder::AddInclude(std::string include, const bool is_system) const
{
	headerSection->AddInclude(include, is_system);
}

void deamer::HFClassBuilder::AddFunction(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType) const
{
	AddFunctionPublic(functionName, args, returnType);
}

void deamer::HFClassBuilder::AddFunctionPrivate(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType) const
{
	_class->AddPrivateMember(functionName, args, returnType);
}

void deamer::HFClassBuilder::AddFunctionProtected(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType) const
{
	_class->AddProtectedMember(functionName, args, returnType);
}

void deamer::HFClassBuilder::AddFunctionPublic(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType) const
{
	_class->AddPublicMember(functionName, args, returnType);
}

void deamer::HFClassBuilder::AddMember(FileVariable* variable) const
{
	AddMemberPrivate(variable);
}

void deamer::HFClassBuilder::AddMemberPrivate(FileVariable* variable) const
{
	_class->AddPublicMember(variable);
}

void deamer::HFClassBuilder::AddMemberProtected(FileVariable* variable) const
{
	_class->AddPublicMember(variable);
}

void deamer::HFClassBuilder::AddMemberPublic(FileVariable* variable) const
{
	_class->AddPublicMember(variable);
}

std::string deamer::HFClassBuilder::GetDefinition() const
{
	return headerSection->GetOutput();
}

std::string deamer::HFClassBuilder::GetImplementation() const
{
	return _class->GetOutputImplementation();
}

std::string deamer::HFClassBuilder::GetOutput() const
{
	return GetDefinition();
}

deamer::FileClassSection* deamer::HFClassBuilder::GetClass()
{
	return _class;
}

void deamer::HFClassBuilder::AddFunction(const char* str) const
{
	FileFunctionSection* tmpFunction = _class->GetCorrespondingVirtualFunction(str);
	if (tmpFunction != nullptr)
		_class->AddPublicMember(tmpFunction->GetFunctionName(), tmpFunction->GetFunctionArgs(), tmpFunction->GetReturnType(), false, true);
}
