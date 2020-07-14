/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/FileBuilder/FileBuilder.h"
#include <string>
#include <fstream>
#include <functional>
#include <ostream>

deamer::FileBuilder::FileBuilder(Directory* directory, File* file)
{
	_Directory = directory;
	_File = file;
	fileSection = new FileSection(directory, file);
}

deamer::FileBuilder::~FileBuilder()
{
	
}

std::string deamer::FileBuilder::GetOutput() const
{
	return fileSection->GetOutput();
}

deamer::File* deamer::FileBuilder::GetFile() const
{
	return _File;
}

deamer::Directory* deamer::FileBuilder::GetDirectory() const
{
	return _Directory;
}

std::string deamer::FileBuilder::GetFileLocationAbsolute() const
{
	return "";
}

std::string deamer::FileBuilder::GetFileLocationRelative() const
{
	return _Directory->FormatRelativeDirectoryLocation() + _File->GetFileName() + _File->GetFileExtension();
}

void deamer::FileBuilder::OpenFile(std::fstream* file) const
{
	file->open(GetFileLocationRelative(), std::ios_base::app);
}


std::fstream deamer::FileBuilder::CreateFile() const
{
	std::fstream newFile;
	OpenFile(&newFile);
	newFile.close();
	return newFile;
}

void deamer::FileBuilder::WriteToFile() const
{
	std::fstream newFile = CreateFile();
	OpenFile(&newFile);
	newFile << FileBuilder::GetOutput();
	newFile.close();
}
