/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEBUILDER_TYPES_FILENAMESPACESECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILENAMESPACESECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include "Deamer/FileBuilder/FileVariableType.h"
#include <string>

namespace deamer
{
	class StringBuilder;

	class FileNamespaceSection : public FileSection, public FileVariableType
	{
		private:
		protected:
			std::string _namespaceName;
			FileNamespaceSection* _baseNamespace;
		
			void AddNamespaceDeclaration(StringBuilder* beginDeclarations, StringBuilder* endDeclarations, unsigned* depth, unsigned indent, bool firstNamespace) const;
			void AddEndingNamespaceDeclaration(StringBuilder* endDeclarations, unsigned indentSize, unsigned depth) const;
			std::string GetThisNamespaceDeclarationWithoutNestedBaseNamespaceDeclarations() const;
			void AddNamespaceTypeToStringBuilder(StringBuilder* stringBuilder, unsigned* depth, bool firstNamespace) const;
			void AddFileSectionOutputToStringBuilder(StringBuilder* string_builder);
		public:
			FileNamespaceSection(std::string namespaceName);
			FileNamespaceSection(FileNamespaceSection* baseNamespace, std::string namespaceName);
			~FileNamespaceSection() = default;
			std::string GetOutput() override;
			std::string GetOutputType() const override;
			std::string GetNamespaceName() const;
			std::string EmbedThisString(std::string string_that_needs_to_be_embedded) const;
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILENAMESPACESECTION_H