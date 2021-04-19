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

#ifndef DEAMER_FILE_TOOL_OUTPUT_H
#define DEAMER_FILE_TOOL_OUTPUT_H

#include "Deamer/File/Tool/Directory.h"
#include <string>

namespace deamer::file::tool
{
	class Data;

	class Output
	{
	private:
		std::string toolDirectory;

		// The directories are automatically placed on the right spots.
		Directory external;
		Directory include;
		Directory library;

	public:
		Output(const std::string& toolDirectory_);
		virtual ~Output() = default;

	public:
		void AddDirectoryToExternal(const Directory& newDirectory);
		void AddDirectoryToInclude(const Directory& newDirectory);
		void AddDirectoryToLibrary(const Directory& newDirectory);

		void AddFileToExternal(const File& newFile);
		void AddFileToInclude(const File& newFile);
		void AddFileToLibrary(const File& newFile);

		void AddCMakeListsToExternal(const CMakeLists& newFile);
		void AddCMakeListsToInclude(const CMakeLists& newFile);
		void AddCMakeListsToLibrary(const CMakeLists& newFile);

		void
		AddActionToExternal(const deamer::file::tool::Action& action,
							const deamer::file::tool::OSType os = deamer::file::tool::OSType::all);

		void
		AddActionToInclude(const deamer::file::tool::Action& action,
						   const deamer::file::tool::OSType os = deamer::file::tool::OSType::all);

		void
		AddActionToLibrary(const deamer::file::tool::Action& action,
						   const deamer::file::tool::OSType os = deamer::file::tool::OSType::all);

	public:
		std::string GetToolDirectory() const;

		Directory GetExternalDirectory() const;
		Directory GetIncludeDirectory() const;
		Directory GetLibraryDirectory() const;

	public:
		/*!	\fn Merge
		 *
		 *	\brief This function merges multiple outputs.
		 *
		 *	\details This function merges multiple outputs,
		 *	this allows the user to more easily define single Outputs,
		 *	and combine them later.
		 *	The alternative would be to manually add directories to existing
		 *	outputs, this is very error prone.
		 */
		static Output Merge(const std::vector<Output>& outputs);

		deamer::file::tool::Output& operator+=(const Output& output);
	};
}

#endif // DEAMER_FILE_TOOL_OUTPUT_H
