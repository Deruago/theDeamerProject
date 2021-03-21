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

#include "Deamer/File/Tool/Output.h"

deamer::file::tool::Output::Output(const std::string& toolDirectory_)
	: toolDirectory(toolDirectory_),
	  external(Directory(toolDirectory_)),
	  include(Directory(toolDirectory_)),
	  library(Directory(toolDirectory_))
{
}

void deamer::file::tool::Output::AddDirectoryToExternal(const Directory& newDirectory)
{
	external.AddDirectory(newDirectory);
}

void deamer::file::tool::Output::AddDirectoryToInclude(const Directory& newDirectory)
{
	include.AddDirectory(newDirectory);
}

void deamer::file::tool::Output::AddDirectoryToLibrary(const Directory& newDirectory)
{
	library.AddDirectory(newDirectory);
}

void deamer::file::tool::Output::AddFileToExternal(const File& newFile)
{
	external.AddFile(newFile);
}

void deamer::file::tool::Output::AddFileToInclude(const File& newFile)
{
	include.AddFile(newFile);
}

void deamer::file::tool::Output::AddFileToLibrary(const File& newFile)
{
	library.AddFile(newFile);
}

std::string deamer::file::tool::Output::GetToolDirectory() const
{
	return toolDirectory;
}

deamer::file::tool::Directory deamer::file::tool::Output::GetExternalDirectory() const
{
	return external;
}

deamer::file::tool::Directory deamer::file::tool::Output::GetIncludeDirectory() const
{
	return include;
}

deamer::file::tool::Directory deamer::file::tool::Output::GetLibraryDirectory() const
{
	return library;
}