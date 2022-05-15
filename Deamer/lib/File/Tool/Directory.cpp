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
#include <iostream>

deamer::file::tool::Directory::Directory()
{
	this->action = std::make_unique<action::Action>();
}

deamer::file::tool::Directory::Directory(const std::string& directoryName_)
	: directoryName(directoryName_)
{
	if (directoryName_.empty())
	{
		throw std::logic_error("Directory name is empty");
	}
	this->action = std::make_unique<action::Action>();
}

deamer::file::tool::Directory::Directory(const Directory& rhs)
{
	this->directoryName = rhs.directoryName;
	this->files = rhs.files;
	this->directories = rhs.directories;
	if (rhs.action == nullptr)
	{
		this->action = nullptr;
	}
	else
	{
		this->action = rhs.action->Copy();
	}
	this->parent = rhs.parent;
	this->cmakeLists = rhs.cmakeLists;
}

deamer::file::tool::Directory& deamer::file::tool::Directory::operator=(const Directory& rhs)
{
	if (&rhs == this)
	{
		return *this;
	}

	this->directoryName = rhs.directoryName;
	this->files = rhs.files;
	this->directories = rhs.directories;
	if (rhs.action == nullptr)
	{
		this->action = nullptr;
	}
	else
	{
		this->action = rhs.action->Copy();
	}
	this->parent = rhs.parent;
	this->cmakeLists = rhs.cmakeLists;

	return *this;
}

deamer::file::tool::Directory& deamer::file::tool::Directory::operator=(Directory&& rhs) noexcept
{
	if (&rhs == this)
	{
		return *this;
	}

	this->directoryName = std::move(rhs.directoryName);
	this->files = std::move(rhs.files);
	this->directories = std::move(rhs.directories);
	this->action = std::move(rhs.action);
	this->parent = std::move(rhs.parent);
	this->cmakeLists = std::move(rhs.cmakeLists);

	return *this;
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

void deamer::file::tool::Directory::AddAction(
	std::unique_ptr<deamer::file::tool::action::Action> action_)
{
	if (action == nullptr)
	{
		action = std::move(action_);
	}
	else
	{
		*action += *action_;
	}
}

void deamer::file::tool::Directory::AddAction(deamer::file::tool::Action action_)
{
	AddAction(action_.GetGeneralAction());
}

void deamer::file::tool::Directory::SetCMakeLists(const std::string& cmakeLists_)
{
	cmakeLists.SetCMakeLists(cmakeLists_);
}

void deamer::file::tool::Directory::SetCMakeLists(const CMakeLists& cmakeLists_)
{
	cmakeLists = cmakeLists_;
}

bool deamer::file::tool::Directory::Empty() const
{
	return directories.empty() && files.empty() && action->IsEmpty();
}

bool deamer::file::tool::Directory::Useless() const
{
	if (!files.empty() || !action->IsEmpty())
	{
		return false;
	}

	if (directories.empty())
	{
		return true;
	}

	// If directories are not empty, check if their structure is useless
	for (const auto& directory : directories)
	{
		if (!directory.Useless())
		{
			return false;
		}
	}

	return true;
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

const deamer::file::tool::action::Action& deamer::file::tool::Directory::GetAction() const
{
	return *action;
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
