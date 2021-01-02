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

#ifndef DEAMER_FILEBUILDER_FILEBUILDER_H
#define DEAMER_FILEBUILDER_FILEBUILDER_H
#include <string>

namespace deamer
{
	class FileSection;
	class File;
	class Directory;
	
	class FileBuilder
	{
		private:
			FileSection* fileSection;
			void OpenFile(std::fstream* file) const;
		protected:
			File* _File;
			Directory* _Directory;
			std::string FileLocationRelative;
			std::string FileLocationAbsolute;
			std::string Output;
			bool IsDirectoryRelative(std::string Directory);
			bool IsDirectoryAbsolute(std::string Directory);
			bool DirectoryLocationStartsWithCorrectIdentifier(const std::string directory);
			std::string FormatDirectoryLocation();
			std::string FormatRelativeDirectoryLocation();
		public:
			FileBuilder(Directory* directory, File* file);
			virtual ~FileBuilder();
			virtual std::string GetOutput() const;
			deamer::File* GetFile() const;
			deamer::Directory* GetDirectory() const;
			std::string GetFileLocationRelative() const;
			std::string GetFileLocationAbsolute() const;
			std::fstream CreateFile() const;
			void WriteToFile() const;
	};
}

#endif //DEAMER_FILEBUILDER_FILEBUILDER_H