/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEBUILDER_FILEBUILDER_H
#define DEAMER_FILEBUILDER_FILEBUILDER_H
#include "Deamer/FileBuilder/FileSection.h"
#include "Deamer/FileBuilder/File.h"
#include "Deamer/FileBuilder/Directory.h"
#include <string>

namespace deamer
{
	class FileSection;
	
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
			~FileBuilder();
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