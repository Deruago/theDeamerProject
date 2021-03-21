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

	public:
		std::string GetToolDirectory() const;

		Directory GetExternalDirectory() const;
		Directory GetIncludeDirectory() const;
		Directory GetLibraryDirectory() const;
	};
}

#endif // DEAMER_FILE_TOOL_OUTPUT_H
