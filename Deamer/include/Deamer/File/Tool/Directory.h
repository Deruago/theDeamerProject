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

#include "Deamer/File/Tool/File.h"
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

	public:
		Directory(const std::string& directoryName_);
		virtual ~Directory() = default;

	public:
		void AddFile(const File& newFile);
		void AddDirectory(const Directory& newDirectory);

	public:
		std::vector<File> GetFiles() const;
		std::vector<Directory> GetDirectories() const;
		std::string GetThisDirectory() const;
	};
}

#endif // DEAMER_FILE_TOOL_DIRECTORY_H
