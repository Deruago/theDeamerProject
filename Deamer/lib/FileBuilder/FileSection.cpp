/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/FileBuilder/FileSection.h"

deamer::FileSection::FileSection(Directory* directory, File* file)
{
	_File = file;
	_Directory = directory;
	FileLocationAbsolute = "CURRENTLY DEPRECATED";
	FileLocationRelative = "CURRENTLY DEPRECATED";
}

std::string deamer::FileSection::GetOutput()
{
	Output = "";
	for(deamer::FileSection* section : FileSections)
	{
		Output += section->GetOutput();
	}
	return Output;
}

void deamer::FileSection::AddSection(FileSection* newSection)
{
	FileSections.push_back(newSection);
}

deamer::Directory* deamer::FileSection::GetDirectory() const
{
	return _Directory;
}

deamer::File* deamer::FileSection::GetFile() const
{
	return _File;
}
