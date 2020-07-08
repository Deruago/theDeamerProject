/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEBUILDER_TYPES_FILEHEADERGUARDSECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEHEADERGUARDSECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include "Deamer/FileBuilder/File.h"
#include "Deamer/FileBuilder/Directory.h"
#include "Deamer/StringBuilder/StringBuilder.h"

namespace deamer
{
	class FileHeaderGuardSection : public FileSection
	{
		private:
		protected:
			std::string HeaderGuardBegin;
			std::string HeaderGuardEnd;
			void AddFileToHeaderGuardMacro(StringBuilder* string, const File* file);
			void AddDirectoryToHeaderGuardMacro(StringBuilder* string, const Directory* directory);
			std::string GetHeaderGuardMacro(const Directory* directory, const File* file);
			std::string GetHeaderGuardMacroDefinition(const Directory* directory, const File* file);
			std::string GetHeaderGuardMacroIfNotDefinedCheck(const Directory* directory, const File* file);
			void SetHeaderGuardBegin(const Directory* directory, const File* file);
			void SetHeaderGuardEnd(const Directory* directory, const File* file);
		public:
			FileHeaderGuardSection(Directory* directory, File* file);
			~FileHeaderGuardSection() = default;
			std::string GetHeaderGuardBegin() const;
			std::string GetHeaderGuardEnd() const;
			std::string GetOutput() override;
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEHEADERGUARDSECTION_H