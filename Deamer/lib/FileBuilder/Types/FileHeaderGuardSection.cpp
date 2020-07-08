#include "Deamer/FileBuilder/Types/FileHeaderGuardSection.h"
#include "Deamer/StringBuilder/StringBuilder.h"
#include <iostream>

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
