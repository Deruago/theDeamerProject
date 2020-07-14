/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/FileBuilder/Directory.h"

deamer::Directory::Directory(std::vector<std::string> directories)
{
	Directories = directories;
}

//deamer::Directory::Directory(std::vector<Directory*> directories)
//{
//}

std::string deamer::Directory::GetDirectoryName()
{
	return *Directories.end();
}

std::vector<std::string> deamer::Directory::GetDirectoryFullPath() const
{
	return Directories;
}

bool deamer::Directory::IsDirectoryRelative(std::string Directory)
{
	return Directory.rfind("./", 0) == 0;
}

bool deamer::Directory::IsDirectoryAbsolute(std::string Directory)
{
	return Directory.rfind("/", 0) == 0;
}

std::string deamer::Directory::FormatRelativeDirectoryLocation()
{
	return GetDirectoryFullPathSingleString();
}

bool deamer::Directory::DirectoryLocationStartsWithCorrectIdentifier(const std::string directory)
{
	return IsDirectoryAbsolute(directory) || IsDirectoryRelative(directory);
}

std::string deamer::Directory::FormatDirectoryLocation()
{
	if (!DirectoryLocationStartsWithCorrectIdentifier(GetDirectoryName()))
	{
		return FormatRelativeDirectoryLocation();
	}
	return GetDirectoryName();
}

std::string deamer::Directory::GetDirectoryFullPathSingleString()
{
	std::string formattedString = "./";
	for(std::string directory : Directories)
	{
		formattedString += directory + "/";
	}
	return formattedString;
}
