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

#include "Deamer/FileBuilder/FileSection.h"
#include "Deamer/FileBuilder/Directory.h"
#include "Deamer/FileBuilder/File.h"
#include <string>

deamer::FileSection::FileSection(Directory* directory, File* file)
{
	_File = file;
	_Directory = directory;
	FileLocationAbsolute = "CURRENTLY DEPRECATED";
	FileLocationRelative = "CURRENTLY DEPRECATED";
}

deamer::FileSection::FileSection()
{
	_File = nullptr;
	_Directory = nullptr;
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