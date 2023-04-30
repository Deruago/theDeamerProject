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

#ifndef DEAMER_FILE_TOOL_LOADFILESYSTEM_H
#define DEAMER_FILE_TOOL_LOADFILESYSTEM_H

#include "Deamer/File/Tool/Directory.h"
#include "Deamer/File/Tool/File.h"
#include <filesystem>
#include <optional>
#include <string>

namespace deamer::file::tool
{
	class LoadFilesystem
	{
	private:
		deamer::file::tool::Directory& outputDir;
		std::string startingDir;

		std::vector<std::string> directories;
		std::vector<std::string> files;
		bool reachedRoot = false;
		bool error_state = false;

	public:
		/*!	\fn LoadFilesystem
		 *	\param outputDir_ Directory used to store found structures
		 *	\param startingDir_ Starting directory
		 */
		LoadFilesystem(deamer::file::tool::Directory& outputDir_,
					   const std::string& startingDir_ = "./");

		/*!	\fn Upper
		 *	\brief Loads the upper directory
		 */
		LoadFilesystem& Upper();

		/*!	\fn RecursiveExpand
		 *	\brief Recursively expands underlying filesystem
		 */
		LoadFilesystem& RecursiveExpand();

		/*!	\fn DirectLoad
		 *	\brief Loads direct members.
		 */
		LoadFilesystem& DirectLoad();

		/*!	\fn Enter
		 *	\brief Enters direct subdirectory
		 *
		 *	\note Only use the directory name. Do not append any directory:
		 *		Good: ".deamer"
		 *		Bad:  "./.deamer"
		 */
		LoadFilesystem& Enter(const std::string& path);

		std::vector<std::string> GetDirectDirectories() const;
		std::vector<std::string> GetDirectFiles() const;
		bool DirectContainsDirectory(const std::string& directoryName) const;
		bool DirectContainsFile(const std::string& fileName) const;
		bool ReachedRoot() const;
		std::string GetPath() const;

		/*!	\fn Error
		 *	\brief If true an error has occured
		 */
		bool Error() const;

	public:
		/*!	\fn GetDeamerDir
		 *	\brief Returns relative path from executable to .deamer project.
		 */
		static std::optional<std::string> GetDeamerDir();

	private:
		void LoadPath(bool loadContent = false);
		deamer::file::tool::Directory LoadDirectory(const std::filesystem::directory_entry& iter);
		deamer::file::tool::File LoadFile(const std::filesystem::directory_entry& iter,
										  bool loadContent = false);
	};
}

#endif // DEAMER_FILE_TOOL_LOADFILESYSTEM_H
