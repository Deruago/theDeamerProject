/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

/*
 * FileSection is used to define "Sections".
 * Sections are important. They are used to create files.
 * Now sections are general and only apply for c++. Later there will be options to have language specific sections.
 * But the idea of sections is to make specific logic for specific cases.
 * e.g a class section needs to define functions, and a functionsection needs to define a function.
 */

#ifndef DEAMER_FILEBUILDER_FILESECTION_H
#define DEAMER_FILEBUILDER_FILESECTION_H
#include <vector>
#include <string>

namespace deamer
{
	class Directory;
	class File;
	
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
			void AddSection(FileSection* newSection); // Used to add sections to a class.
		public:
			FileSection(Directory* directory, File* file);
			FileSection();
			~FileSection() = default;
			virtual std::string GetOutput();
			Directory* GetDirectory() const;
			File* GetFile() const;
			
	};
}

#endif //DEAMER_FILEBUILDER_FILESECTION_H