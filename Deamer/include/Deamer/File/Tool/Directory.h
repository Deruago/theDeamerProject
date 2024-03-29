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

#ifndef DEAMER_FILE_TOOL_DIRECTORY_H
#define DEAMER_FILE_TOOL_DIRECTORY_H

#include "Deamer/File/Tool/Action.h"
#include "Deamer/File/Tool/Action/Action.h"
#include "Deamer/File/Tool/CMakeLists.h"
#include "Deamer/File/Tool/File.h"
#include "Deamer/File/Tool/OSType.h"
#include <string>
#include <vector>

namespace deamer::file::tool
{
	class Directory
	{
	private:
		std::string directoryName;

		std::vector<File> files;
		std::vector<Directory> directories;
		std::unique_ptr<deamer::file::tool::action::Action> action;

		mutable const Directory* parent = nullptr;

		CMakeLists cmakeLists;

	public:
		// Use this to generate an empty directory.
		Directory();

		Directory(const std::string& directoryName_);
		Directory(const Directory& rhs);
		virtual ~Directory() = default;

	public:
		Directory& operator=(const Directory& rhs);
		Directory& operator=(Directory&& rhs) noexcept;

	public:
		void AddFile(const File& newFile);
		void AddDirectory(const Directory& newDirectory);
		void AddAction(std::unique_ptr<deamer::file::tool::action::Action> action_);
		void AddAction(deamer::file::tool::Action action_);

		void SetCMakeLists(const std::string& cmakeLists_);
		void SetCMakeLists(const CMakeLists& cmakeLists_);

	public:
		// Specifies this directory is useless as it contains nothing
		bool Empty() const;

		// Specifies this directory's structure is useless
		bool Useless() const;

		std::vector<File> GetFiles() const;
		std::vector<Directory> GetDirectories() const;
		std::string GetThisDirectory() const;
		const deamer::file::tool::action::Action& GetAction() const;
		CMakeLists GetCMakeLists() const;

		deamer::file::tool::Directory& operator+=(const Directory& directory);

		std::vector<std::string> SplitDirectoryName() const;

		std::vector<std::string> GetParentPath() const;

		/*!	\fn GetDifferenceOfDirectoryName
		 *
		 *	\brief Returns the difference between two directory names
		 *	example:
		 *		our        = "ast/node"
		 *		theirs     = "ast/node/visitor/generated/"
		 *		difference = "visitor/generated/"
		 */
		std::vector<std::string>
		GetDifferenceOfDirectoryName(const Directory& comparedDirectory) const;

		/*!	\fn CopyDirectoryAsLocalDirectory
		 *
		 *	\brief Returns the directory as if it was part of the current directory.
		 */
		deamer::file::tool::Directory CopyDirectoryAsLocalDirectory() const;

	private:
		Directory& GetLocalDirectory(const std::string& requestedDirectory);
		bool IsDirectoryAlreadyCreated(const std::string& directoryName);
	};
}

#endif // DEAMER_FILE_TOOL_DIRECTORY_H
