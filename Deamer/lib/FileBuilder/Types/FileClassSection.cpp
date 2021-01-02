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

#include "Deamer/FileBuilder/Types/FileClassSection.h"
#include "Deamer/FileBuilder/Types/FileNamespaceSection.h"
#include "Deamer/FileBuilder/Types/FileFunctionSection.h"
#include "Deamer/StringBuilder/StringBuilder.h"
#include "Deamer/FileBuilder/Types/FileFunctionPrototypeSection.h"
#include <vector>
#include <string>

deamer::FileClassSection::FileClassSection(std::string className) : FileVariable(this, className, true)
{
	_namespace = nullptr;
}

deamer::FileClassSection::FileClassSection(std::string className, FileNamespaceSection* scope) : FileVariable(this, className, true)
{
	_namespace = scope;
}

deamer::FileClassSection::FileClassSection(std::string className, std::vector<FileClassSection*> superClasses,
                                           FileNamespaceSection* scope) : FileClassSection(className, scope)
{
	_superClasses = superClasses;
	AddVirtualMemberFunctionsFromBaseClasses();
}

deamer::FileClassSection::~FileClassSection()
{
	delete_members(privateMembers);
	delete_members(protectedMembers);
	delete_members(publicMembers);
	delete_members(privateMemberFunctions);
	delete_members(protectedMemberFunctions);
	delete_members(publicMemberFunctions);
}

std::string deamer::FileClassSection::GetOutputDeclarationWithoutNamespace() const
{
	StringBuilder stringBuilder;
	AddSuperClassForwardDeclarations(&stringBuilder);
	stringBuilder.Add();
	AddClassBeginningDeclaration(&stringBuilder);
	AddPrivateSectionToStringBuilder(&stringBuilder);
	AddProtectedSectionToStringBuilder(&stringBuilder);
	AddPublicSectionToStringBuilder(&stringBuilder);
	AddClassEndDeclaration(&stringBuilder);

	return stringBuilder.GetOutput();
}

std::string deamer::FileClassSection::GetOutputDeclaration() const
{
	if (_namespace != nullptr)
	{
		return _namespace->EmbedThisString(GetOutputDeclarationWithoutNamespace());
	}
	else
	{
		return GetOutputDeclarationWithoutNamespace();
	}
}

std::string deamer::FileClassSection::GetOutputImplementation() const
{
	return "";
}

std::string deamer::FileClassSection::GetOutput()
{
	return GetOutputDeclaration();
}

std::string deamer::FileClassSection::GetOutputType() const
{
	StringBuilder stringBuilder;
	AddNamespace(&stringBuilder);
	AddClass(&stringBuilder);
	return stringBuilder.GetOutputIgnoreNewLine();
}

std::string deamer::FileClassSection::GetForwardDeclaration() const
{
	StringBuilder stringBuilder;
	stringBuilder.Add("class ");
	stringBuilder.Add(GetClassName());
	stringBuilder.Add(";");
	return stringBuilder.GetOutputIgnoreNewLine();
}

void deamer::FileClassSection::AddSuperClassForwardDeclarations(StringBuilder* stringBuilder) const
{
	for(FileClassSection* classSections : _superClasses)
	{
		stringBuilder->Add(classSections->GetForwardDeclaration());
	}
}

void deamer::FileClassSection::AddClassBeginningDeclaration(StringBuilder* string_builder) const
{
	StringBuilder tmp_string_builder;
	tmp_string_builder.Add("class ");
	tmp_string_builder.Add(GetClassName());
	AddSuperClassInheritanceToStringBuilder(&tmp_string_builder);
	string_builder->Add(tmp_string_builder.GetOutputIgnoreNewLine());
	string_builder->Add("{");
}

void deamer::FileClassSection::AddSuperClassInheritanceToStringBuilder(StringBuilder* string_builder) const
{
	if (!_superClasses.empty())
	{
		string_builder->Add(" : ");
	}
	
	for(int i = 0; i < _superClasses.size(); i++)
	{
		string_builder->Add("public ");
		string_builder->Add(_superClasses[i]->GetClassName());
		if (i < _superClasses.size() - 1)
		{
			string_builder->Add(", ");
		}
	}
}

void deamer::FileClassSection::AddPrivateSectionToStringBuilder(StringBuilder* string_builder) const
{
	string_builder->Add(GetPrivateSection());
}

void deamer::FileClassSection::AddProtectedSectionToStringBuilder(StringBuilder* string_builder) const
{
	string_builder->Add(GetProtectedSection());
}

void deamer::FileClassSection::AddPublicSectionToStringBuilder(StringBuilder* string_builder) const
{
	string_builder->Add(GetPublicSection());
}

void deamer::FileClassSection::AddClassEndDeclaration(StringBuilder* string_builder) const
{
	string_builder->Add("};");
}


void deamer::FileClassSection::AddClass(StringBuilder* stringBuilder) const
{
	stringBuilder->Add(GetClassName());
}

void deamer::FileClassSection::AddNamespace(StringBuilder* stringBuilder) const
{
	if (_namespace != nullptr)
	{
		stringBuilder->Add(GetNamespace());
		stringBuilder->Add("::");
	}
}

std::string deamer::FileClassSection::GetClassName() const
{
	return GetVariableName();
}

std::string deamer::FileClassSection::GetNamespace() const
{
	if (_namespace == nullptr)
	{
		return "";
	}
	return _namespace->GetOutputType();
}

void deamer::FileClassSection::CreateClassSectionStringBuilder(std::string sectionType, StringBuilder* stringBuilder) const
{
	stringBuilder->Add(sectionType + ":");
}

void deamer::FileClassSection::AddPrivateMembersToStringBuilder(StringBuilder* stringBuilder) const
{
	for (FileVariable* members : privateMembers)
	{
		stringBuilder->Add(members->GetOutput(), 4, 1);
	}
}

void deamer::FileClassSection::AddPrivateMemberFunctionsToStringBuilder(StringBuilder* stringBuilder) const
{
	for (FileFunctionSection* memberFunctions : privateMemberFunctions)
	{
		stringBuilder->Add(memberFunctions->GetFunctionPrototypeOutput(false, true), 4, 1);
	}
}

std::string deamer::FileClassSection::GetPrivateSection() const
{
	StringBuilder stringBuilder;
	CreateClassSectionStringBuilder("private", &stringBuilder);
	AddPrivateMembersToStringBuilder(&stringBuilder);

	if (!privateMembers.empty()) stringBuilder.Add();
	AddPrivateMemberFunctionsToStringBuilder(&stringBuilder);
	return stringBuilder.GetOutput();
}

void deamer::FileClassSection::AddProtectedMembersToStringBuilder(StringBuilder* stringBuilder) const
{
	for (FileVariable* members :protectedMembers)
	{
		stringBuilder->Add(members->GetOutput(), 4, 1);
	}
}

void deamer::FileClassSection::AddProtectedMemberFunctionsToStringBuilder(StringBuilder* stringBuilder) const
{
	for (FileFunctionSection* memberFunctions :protectedMemberFunctions)
	{
		stringBuilder->Add(memberFunctions->GetFunctionPrototypeOutput(false, true), 4, 1);
	}
}

std::string deamer::FileClassSection::GetProtectedSection() const
{
	StringBuilder stringBuilder;
	CreateClassSectionStringBuilder("protected", &stringBuilder);
	AddProtectedMembersToStringBuilder(&stringBuilder);

	if (!protectedMembers.empty()) stringBuilder.Add();

	AddProtectedMemberFunctionsToStringBuilder(&stringBuilder);

	return stringBuilder.GetOutput();
}

void deamer::FileClassSection::AddPublicMembersToStringBuilder(StringBuilder* stringBuilder) const
{
	for (FileVariable* members : publicMembers)
	{
		stringBuilder->Add(members->GetOutput(), 4, 1);
	}
}

void deamer::FileClassSection::AddPublicMemberFunctionsToStringBuilder(StringBuilder* stringBuilder) const
{
	for (FileFunctionSection* memberFunctions : publicMemberFunctions)
	{
		stringBuilder->Add(memberFunctions->GetFunctionPrototypeOutput(false, true), 4, 1);
	}
}


std::string deamer::FileClassSection::GetPublicSection() const
{
	StringBuilder stringBuilder;
	CreateClassSectionStringBuilder("public", &stringBuilder);
	AddPublicMembersToStringBuilder(&stringBuilder);

	if (!publicMembers.empty()) stringBuilder.Add();

	AddPublicMemberFunctionsToStringBuilder(&stringBuilder);

	return stringBuilder.GetOutput();
}

std::vector<deamer::FileFunctionSection*> deamer::FileClassSection::GetPrivateMemberFunctions() const
{
	return privateMemberFunctions;
}

std::vector<deamer::FileVariable*> deamer::FileClassSection::GetPrivateMemberVariables() const
{
	return privateMembers;
}

std::vector<deamer::FileFunctionSection*> deamer::FileClassSection::GetProtectedMemberFunctions() const
{
	return protectedMemberFunctions;
}

std::vector<deamer::FileVariable*> deamer::FileClassSection::GetProtectedMemberVariables() const
{
	return protectedMembers;
}

std::vector<deamer::FileFunctionSection*> deamer::FileClassSection::GetPublicMemberFunctions() const
{
	return publicMemberFunctions;
}

std::vector<deamer::FileVariable*> deamer::FileClassSection::GetPublicMemberVariables() const
{
	return publicMembers;
}

void deamer::FileClassSection::AddPrivateMember(FileVariable* member)
{
	privateMembers.push_back(member);
}

void deamer::FileClassSection::AddProtectedMember(FileVariable* member)
{
	protectedMembers.push_back(member);
}

void deamer::FileClassSection::AddPublicMember(FileVariable* member)
{
	publicMembers.push_back(member);
}

void deamer::FileClassSection::AddPrivateMember(FileFunctionSection* memberFunction)
{
	privateMemberFunctions.push_back(memberFunction);
}

void deamer::FileClassSection::AddProtectedMember(FileFunctionSection* memberFunction)
{
	protectedMemberFunctions.push_back(memberFunction);
}

void deamer::FileClassSection::AddPublicMember(FileFunctionSection* memberFunction)
{
	publicMemberFunctions.push_back(memberFunction);
}

void deamer::FileClassSection::AddPrivateMember(std::string functionName, std::vector<FileVariable*> args,
	FileVariableType* returnType)
{
	privateMemberFunctions.push_back(new FileFunctionSection(functionName, args, returnType, this));
}

void deamer::FileClassSection::AddProtectedMember(std::string functionName, std::vector<FileVariable*> args,
	FileVariableType* returnType)
{
	protectedMemberFunctions.push_back(new FileFunctionSection(functionName, args, returnType, this));
}

void deamer::FileClassSection::AddPublicMember(std::string functionName, std::vector<FileVariable*> args,
	FileVariableType* returnType)
{
	publicMemberFunctions.push_back(new FileFunctionSection(functionName, args, returnType, this));
}

void deamer::FileClassSection::AddPublicMember(std::string functionName, std::vector<FileVariable*> args,
	FileVariableType* returnType, bool isVirtual)
{
	publicMemberFunctions.push_back(new FileFunctionSection(new FileFunctionPrototypeSection(functionName, args, returnType, this, false, isVirtual)));
}

deamer::FileFunctionSection* deamer::FileClassSection::GetCorrespondingVirtualFunction(const char* str)
{
	for(FileClassSection* _superClass : _superClasses)
	{
		FileFunctionSection* tmpFunction = _superClass->GetCorrespondingVirtualFunction(str);
		if(tmpFunction != nullptr)
		{
			return tmpFunction;
		}
	}

	for(FileFunctionSection* function : publicMemberFunctions)
	{
		if (function->GetFunctionName() == str)
		{
			return function;
		}
	}

	for (FileFunctionSection* function : publicMemberFunctions)
	{
		if (function->GetFunctionName() == str)
		{
			return function;
		}
	}

	for (FileFunctionSection* function : publicMemberFunctions)
	{
		if (function->GetFunctionName() == str)
		{
			return function;
		}
	}
	return nullptr;
}

void deamer::FileClassSection::AddPublicMember(const std::string& cs, const std::vector<FileVariable*>& args,
	FileVariableType* file_variable, bool is_virtual, bool _override)
{
	publicMemberFunctions.push_back(new FileFunctionSection(new FileFunctionPrototypeSection(cs, args, file_variable, this, false, is_virtual, _override)));
}

void deamer::FileClassSection::AddVirtualMemberFunctionsFromBaseClasses()
{
	for(FileClassSection* base_class : _superClasses)
	{
		AddFunctionsToVector(CopyFunctionsAsOverridenFunctions(base_class->GetPrivateVirtualMemberFunctions()), this->privateMemberFunctions);
		AddFunctionsToVector(CopyFunctionsAsOverridenFunctions(base_class->GetProtectedVirtualMemberFunctions()), this->protectedMemberFunctions);
		AddFunctionsToVector(CopyFunctionsAsOverridenFunctions(base_class->GetPublicVirtualMemberFunctions()), this->publicMemberFunctions);
	}
}


std::vector<deamer::FileFunctionSection*> deamer::FileClassSection::GetPrivateVirtualMemberFunctions()
{
	return GetVirtualMemberFunctionsFromVector(privateMemberFunctions);
}

std::vector<deamer::FileFunctionSection*> deamer::FileClassSection::GetProtectedVirtualMemberFunctions()
{
	return GetVirtualMemberFunctionsFromVector(protectedMemberFunctions);
}

std::vector<deamer::FileFunctionSection*> deamer::FileClassSection::GetPublicVirtualMemberFunctions()
{
	return GetVirtualMemberFunctionsFromVector(publicMemberFunctions);
}

std::vector<deamer::FileFunctionSection*> deamer::FileClassSection::GetVirtualMemberFunctionsFromVector(
	const std::vector<FileFunctionSection*>& vector)
{
	std::vector<FileFunctionSection*> tmpVector;
	for(FileFunctionSection* function : vector)
	{
		if(function->IsVirtual())
		{
			tmpVector.push_back(function);
		}
	}
	return tmpVector;
}

std::vector<deamer::FileFunctionSection*> deamer::FileClassSection::CopyFunctionsAsOverridenFunctions(const std::vector<FileFunctionSection*>& vector)
{
	std::vector<FileFunctionSection*> newFunctions;
	newFunctions.reserve(vector.size());
	for(FileFunctionSection* old_function : vector)
	{
		newFunctions.push_back(new FileFunctionSection(new FileFunctionPrototypeSection(old_function->GetFunctionName(), old_function->GetFunctionArgs(), old_function->GetReturnType(), this, false, false, true)));
	}
	return newFunctions;
}

void deamer::FileClassSection::AddFunctionsToVector(const std::vector<FileFunctionSection*>& vector,
	std::vector<FileFunctionSection*>& file_function_sections)
{
	for(FileFunctionSection* function : vector)
	{
		file_function_sections.push_back(function);
	}
}
