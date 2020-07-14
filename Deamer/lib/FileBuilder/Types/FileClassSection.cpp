#include "Deamer/FileBuilder/Types/FileClassSection.h"
#include "Deamer/FileBuilder/FileVariable.h"
#include "Deamer/FileBuilder/FileVariableType.h"
#include "Deamer/FileBuilder/Types/FileNamespaceSection.h"
#include "Deamer/FileBuilder/Types/FileFunctionSection.h"
#include "Deamer/StringBuilder/StringBuilder.h"
#include <vector>
#include <string>

deamer::FileClassSection::FileClassSection(std::string className, FileNamespaceSection* scope) : FileVariable(this, className, true)
{
	_namespace = scope;
}

deamer::FileClassSection::FileClassSection(std::string className, std::vector<FileClassSection*> superClasses,
                                           FileNamespaceSection* scope) : FileClassSection(className, scope)
{
	_superClasses = superClasses;
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
		if (i < _superClasses.size())
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
		stringBuilder->Add(memberFunctions->GetFunctionPrototypeOutput(false), 4, 1);
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
		stringBuilder->Add(memberFunctions->GetFunctionPrototypeOutput(false), 4, 1);
	}
}

std::string deamer::FileClassSection::GetProtectedSection() const
{
	StringBuilder stringBuilder;
	CreateClassSectionStringBuilder("Protected", &stringBuilder);
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
		stringBuilder->Add(memberFunctions->GetFunctionPrototypeOutput(false), 4, 1);
	}
}


std::string deamer::FileClassSection::GetPublicSection() const
{
	StringBuilder stringBuilder;
	CreateClassSectionStringBuilder("Public", &stringBuilder);
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
