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

#ifndef DEAMER_FILEBUILDER_DIRECTORY_H
#define DEAMER_FILEBUILDER_DIRECTORY_H
#include <string>
#include <vector>

namespace deamer
{
	class Directory
	{
		private:
			std::string FormatDirectoryLocation();
			std::string GetDirectoryFullPathSingleString();
			bool DirectoryLocationStartsWithCorrectIdentifier(std::string directory);
		protected:
			std::vector<std::string> Directories;
		public:
			Directory(std::vector<std::string> directories);
			//Directory(std::vector<Directory*> directories);
			~Directory() = default;
			std::string GetDirectoryName();
			std::vector<std::string> GetDirectoryFullPath() const;
			std::string FormatRelativeDirectoryLocation();
			bool IsDirectoryRelative(std::string Directory);
			bool IsDirectoryAbsolute(std::string Directory);
	};
}

#endif //DEAMER_FILEBUILDER_DIRECTORY_H