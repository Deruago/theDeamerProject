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

#include "Deamer/File/Tool/Directory.h"

deamer::file::tool::Directory::Directory(const std::string& directoryName_)
	: directoryName(directoryName_)
{
}

void deamer::file::tool::Directory::AddFile(const File& newFile)
{
	files.push_back(newFile);
}

void deamer::file::tool::Directory::AddDirectory(const Directory& newDirectory)
{
	directories.push_back(newDirectory);
}

std::vector<deamer::file::tool::File> deamer::file::tool::Directory::GetFiles() const
{
	return files;
}

std::vector<deamer::file::tool::Directory> deamer::file::tool::Directory::GetDirectories() const
{
	return directories;
}

std::string deamer::file::tool::Directory::GetThisDirectory() const
{
	return directoryName;
}
