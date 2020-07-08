/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEBUILDER_FILESECTION_H
#define DEAMER_FILEBUILDER_FILESECTION_H
#include "Deamer/FileBuilder/FileBuilder.h"
#include "Deamer/FileBuilder/Directory.h"
#include "Deamer/FileBuilder/File.h"
#include <vector>
#include <string>

namespace deamer
{
	class FileBuilder;
	
	class FileSection
	{
		private:
			File* _File;
			Directory* _Directory;
		protected:
			std::string Output;
			std::string FileLocationRelative;
			std::string FileLocationAbsolute;
			std::vector<FileSection*> FileSections;
		public:
			FileSection(Directory* directory, File* file);
			~FileSection() = default;
			virtual std::string GetOutput();
			virtual void AddSection(FileSection* newSection);
			Directory* GetDirectory() const;
			File* GetFile() const;
			
	};
}

#endif //DEAMER_FILEBUILDER_FILESECTION_H