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
	if (directoryName_.empty())
	{
		throw std::logic_error("Directory name is empty");
	}
}

deamer::file::tool::Directory::Directory(const Directory& rhs)
{
	this->directoryName = rhs.directoryName;
	this->files = rhs.files;
	this->directories = rhs.directories;
	this->actions = rhs.actions;
	this->parent = rhs.parent;
	this->cmakeLists = rhs.cmakeLists;
}

void deamer::file::tool::Directory::AddFile(const File& newFile)
{
	files.push_back(newFile);
}

void deamer::file::tool::Directory::AddDirectory(const Directory& newDirectory)
{
	newDirectory.parent = this;
	directories.push_back(newDirectory);
}

void deamer::file::tool::Directory::AddAction(const deamer::file::tool::Action& action,
											  const deamer::file::tool::OSType os)
{
	for (auto existingAction : actions)
	{
		if (existingAction.second == os)
		{
			existingAction.first = existingAction.first.GetAction() + ";" + action.GetAction();
			return;
		}
	}

	actions.emplace_back(action, os);
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

deamer::file::tool::Action
deamer::file::tool::Directory::GetAction(deamer::file::tool::OSType os) const
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

deamer::file::tool::Directory&
deamer::file::tool::Directory::operator+=(const Directory& newDirectory)
{
	if (&newDirectory == this)
	{
		return *this;
	}

	const auto difference = GetDifferenceOfDirectoryName(newDirectory);

	if (difference.empty())
	{
		// UNIMPLEMENTED LOGIC. Cannot merge 2 directories at the same location.

		return *this;
	}

	const auto& rootDifference = difference[0];

	if (difference.size() == 1)
	{
		if (IsDirectoryAlreadyCreated(rootDifference))
		{
			auto& localDirectory = GetLocalDirectory(rootDifference);
			localDirectory += newDirectory;
		}
		else
		{
			AddDirectory(newDirectory.CopyDirectoryAsLocalDirectory());
		}
		return *this;
	}

	// if we aren't at the spot.
	if (IsDirectoryAlreadyCreated(rootDifference))
	{
		auto& localDirectory = GetLocalDirectory(rootDifference);
		localDirectory += newDirectory;
	}
	else
	{
		const Directory newLocalDirectory(rootDifference);
		AddDirectory(newLocalDirectory);
		GetLocalDirectory(rootDifference) += newDirectory;
	}

	return *this;
}

std::vector<std::string> deamer::file::tool::Directory::SplitDirectoryName() const
{
	std::vector<std::string> sections;
	std::string tempString;

	for (auto character : directoryName)
	{
		if (character == '/')
		{
			sections.push_back(tempString);
			tempString = "";
		}
		else
		{
			tempString += character;
		}
	}

	if (!tempString.empty())
	{
		sections.push_back(tempString);
		tempString.clear();
	}

	return sections;
}

std::vector<std::string> deamer::file::tool::Directory::GetParentPath() const
{
	if (parent != nullptr)
	{
		auto parentPath = parent->GetParentPath();
		for (const auto& section : SplitDirectoryName())
		{
			parentPath.push_back(section);
		}

		return parentPath;
	}

	return SplitDirectoryName();
}

std::vector<std::string> deamer::file::tool::Directory::GetDifferenceOfDirectoryName(
	const Directory& comparedDirectory) const
{
	const auto ourSections = GetParentPath();
	auto theirSections = comparedDirectory.GetParentPath();

	if (theirSections.size() < ourSections.size())
	{
		return {};
	}

	for (size_t i = 0; i < ourSections.size() && !theirSections.empty(); i++)
	{
		const auto& currentOurSection = ourSections[i];
		const auto& currentTheirSection = theirSections[0];

		if (currentOurSection == currentTheirSection)
		{
			theirSections.erase(theirSections.begin());
		}
		else
		{
			break;
		}
	}

	return theirSections;
}

deamer::file::tool::Directory deamer::file::tool::Directory::CopyDirectoryAsLocalDirectory() const
{
	Directory directory = *this;
	directory.directoryName = *(SplitDirectoryName().end() - 1);
	return directory;
}

deamer::file::tool::Directory&
deamer::file::tool::Directory::GetLocalDirectory(const std::string& requestedDirectory)
{
	for (auto& dir : directories)
	{
		if (dir.directoryName == requestedDirectory)
		{
			return dir;
		}
	}

	throw std::logic_error("There is no such directory.");
}

bool deamer::file::tool::Directory::IsDirectoryAlreadyCreated(const std::string& directoryName)
{
	for (const auto& dir : directories)
	{
		if (dir.directoryName == directoryName)
		{
			return true;
		}
	}

	return false;
}
