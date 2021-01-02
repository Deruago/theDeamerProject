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