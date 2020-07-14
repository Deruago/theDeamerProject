/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/FileBuilder/Types/FileHeaderSection.h"
#include "Deamer/FileBuilder/Types/FileHeaderGuardSection.h"

deamer::FileHeaderSection::FileHeaderSection(Directory* dir, File* file) : FileSection(dir, file)
{
	headerGuard = AddHeaderGuard(GetDirectory(), GetFile());
}


deamer::FileHeaderGuardSection* deamer::FileHeaderSection::AddHeaderGuard(Directory* directory, File* file)
{
	return new FileHeaderGuardSection(directory, file);
}

std::string deamer::FileHeaderSection::GetOutput()
{
	StringBuilder headerFile;
	headerFile.Add(headerGuard->GetHeaderGuardBegin());

	for(FileSection* file_section : FileSections)
	{
		headerFile.Add(file_section->GetOutput());
	}
	
	headerFile.Add(headerGuard->GetHeaderGuardEnd());
	return headerFile.GetOutput();
}

deamer::FileNamespaceSection* deamer::FileHeaderSection::AddNamespace(std::string namespaceName)
{
	auto newNamespace = new FileNamespaceSection(namespaceName);
	AddSection(newNamespace);
	return newNamespace;
}

deamer::FileClassSection* deamer::FileHeaderSection::AddClass(std::string className,
	std::vector<FileClassSection*> superClasses, FileNamespaceSection* scope)
{
	auto newClass = new FileClassSection(className, superClasses, scope);
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