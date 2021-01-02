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

#include "Deamer/FileBuilder/Directory.h"
#include <vector>
#include <string>

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
