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

namespace deamer
{
	class FileHeaderSection : public FileSection
	{
		private:
			deamer::FileHeaderGuardSection* AddHeaderGuard(Directory* directory, File* file);
		protected:
			FileHeaderGuardSection* headerGuard;
		public:
			FileHeaderSection(Directory* dir, File* file);
			~FileHeaderSection() = default;
			FileNamespaceSection* AddNamespace(std::string namespaceName);
			FileClassSection* AddClass(std::string className, std::vector<std::string> superClasses, std::string scope);
			FileFunctionSection* AddFunction(std::string functionName, std::vector<std::string> functionArgs, std::string returnType, std::string scope);
			std::string GetOutput() override;
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEHEADERSECTION_H
