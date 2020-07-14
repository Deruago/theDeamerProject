/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEBUILDER_TYPES_FILEHEADERSECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEHEADERSECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include "Deamer/FileBuilder/Types/FileClassSection.h"
#include "Deamer/FileBuilder/Types/FileNamespaceSection.h"
#include "Deamer/FileBuilder/Types/FileFunctionSection.h"
#include "Deamer/FileBuilder/Types/FileHeaderGuardSection.h"
#include "Deamer/FileBuilder/Types/FileFunctionPrototypeSection.h"
#include <vector>

namespace deamer
{
	class FileHeaderGuardSection;
	class Directory;
	class File;
	class FileClassSection;
	class FileFunctionSection;
	class FileFunctionPrototypeSection;
	class FileNamespaceSection;
	
	class FileHeaderSection : public FileSection
	{
		private:
			deamer::FileHeaderGuardSection* AddHeaderGuard(Directory* directory, File* file);
			std::vector<FileClassSection*> classes;
			std::vector<FileFunctionSection*> functions;
		protected:
			FileHeaderGuardSection* headerGuard;
		public:
			FileHeaderSection(Directory* dir, File* file);
			~FileHeaderSection() = default;
			FileNamespaceSection* AddNamespace(std::string namespaceName);
			void AddNamespace(FileNamespaceSection* namespaceSection);
			FileClassSection* AddClass(std::string className, std::vector<FileClassSection*> superClasses, FileNamespaceSection* scope);
			void AddClass(FileClassSection* classSection);
			FileFunctionSection* AddFunction(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType*
			                                 scope);
			FileFunctionSection* AddFunction(FileFunctionPrototypeSection* functionPrototype);
			void AddFunction(FileFunctionSection* functionSection);
			std::string GetOutput() override;
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEHEADERSECTION_H
