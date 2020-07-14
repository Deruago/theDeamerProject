/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
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