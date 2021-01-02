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

#include "Deamer/FileBuilder/FileBuilder.h"
#include "Deamer/FileBuilder/FileSection.h"
#include "Deamer/FileBuilder/Directory.h"
#include "Deamer/FileBuilder/File.h"
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
