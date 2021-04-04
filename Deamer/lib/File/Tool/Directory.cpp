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

void deamer::file::tool::Directory::AddAction(const deamer::file::tool::Action& action,
											  const deamer::file::tool::OSType os)
{
	actions.push_back({action, os});
}

void deamer::file::tool::Directory::SetCMakeLists(const std::string& cmakeLists_)
{
	cmakeLists.SetCMakeLists(cmakeLists_);
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

deamer::file::tool::Action deamer::file::tool::Directory::GetAction(deamer::file::tool::OSType os) const
{
	deamer::file::tool::Action currentAction = deamer::file::tool::Action();

	for (const auto& [action, action_os] : actions)
	{
		if (action_os == os)
		{
			currentAction = action;
			break;
		}
		if (action_os == deamer::file::tool::OSType::all)
		{
			currentAction = action;
		}
	}

	return currentAction;
}

deamer::file::tool::CMakeLists deamer::file::tool::Directory::GetCMakeLists() const
{
	return cmakeLists;
}
