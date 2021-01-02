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

/*
 * FileClassSection is used to define a class in c++.
 * If you use the GetOutput function you get a valid Class.
 */

#ifndef DEAMER_FILEBUILDER_TYPES_FILECLASSSECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILECLASSSECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include "Deamer/FileBuilder/FileVariable.h"
#include "Deamer/FileBuilder/FileVariableType.h"
#include <vector>
#include <string>


namespace deamer
{
	class FileNamespaceSection;
	class FileFunctionSection;
	class StringBuilder;

	class FileClassSection : public FileSection, public FileVariableType, public FileVariable
	{
		private:
			FileNamespaceSection* _namespace;
			std::vector<FileClassSection*> _superClasses;
			std::vector<FileVariable*> privateMembers;
			std::vector<FileVariable*> protectedMembers;
			std::vector<FileVariable*> publicMembers;
			std::vector<FileFunctionSection*> privateMemberFunctions;
			std::vector<FileFunctionSection*> protectedMemberFunctions;
			std::vector<FileFunctionSection*> publicMemberFunctions;
		
			void AddClass(StringBuilder* stringBuilder) const;
			void AddNamespace(StringBuilder* stringBuilder) const;
			void CreateClassSectionStringBuilder(std::string sectionType, StringBuilder* stringBuilder) const;
			void AddPrivateMembersToStringBuilder(StringBuilder* stringBuilder) const;
			void AddPrivateMemberFunctionsToStringBuilder(StringBuilder* stringBuilder) const;
			void AddProtectedMembersToStringBuilder(StringBuilder* stringBuilder) const;
			void AddProtectedMemberFunctionsToStringBuilder(StringBuilder* stringBuilder) const;
			void AddPublicMembersToStringBuilder(StringBuilder* stringBuilder) const;
			void AddPublicMemberFunctionsToStringBuilder(StringBuilder* stringBuilder) const;
			void AddSuperClassForwardDeclarations(StringBuilder* stringBuilder) const;

			// Needed for class declaration building
			void AddClassBeginningDeclaration(StringBuilder* string_builder) const;
			void AddSuperClassInheritanceToStringBuilder(StringBuilder* string_builder) const;
			void AddPrivateSectionToStringBuilder(StringBuilder* string_builder) const;
			void AddProtectedSectionToStringBuilder(StringBuilder* string_builder) const;
			void AddPublicSectionToStringBuilder(StringBuilder* string_builder) const;
			void AddClassEndDeclaration(StringBuilder* string_builder) const;
		
			std::vector<FileFunctionSection*> GetVirtualMemberFunctionsFromVector(const std::vector<FileFunctionSection*>& vector);
			std::vector<deamer::FileFunctionSection*> CopyFunctionsAsOverridenFunctions(
				const std::vector<FileFunctionSection*>& vector);
			void AddFunctionsToVector(const std::vector<FileFunctionSection*>& vector, std::vector<FileFunctionSection*>& file_function_sections);
			void AddVirtualMemberFunctionsFromBaseClasses();
		protected:
		public:
			FileClassSection(std::string className); // If the class is a basic class. e.g int, string, char
			FileClassSection(std::string className, FileNamespaceSection* scope); // If the class is a base class.
			FileClassSection(std::string className, std::vector<FileClassSection*> superClasses, FileNamespaceSection* scope); // If the class is a sub class
			~FileClassSection();
			std::string GetOutputDeclarationWithoutNamespace() const;
			std::string GetOutputDeclaration() const;
			std::string GetOutputImplementation() const;
			std::string GetOutput() override; // Defaults to GetOutputDeclaration
			std::string GetOutputType() const override; // Gives the output type. Including namespace
			std::string GetForwardDeclaration() const;
			std::string GetClassName() const;
			std::string GetNamespace() const;

			std::string GetPrivateSection() const;
			std::string GetProtectedSection() const;
			std::string GetPublicSection() const;
		
			std::vector<FileSection*> GetPrivateMembers() const;
			std::vector<FileFunctionSection*> GetPrivateMemberFunctions() const;
			std::vector<FileVariable*> GetPrivateMemberVariables() const;

			std::vector<FileSection*> GetProtectedMembers() const;
			std::vector<FileFunctionSection*> GetProtectedMemberFunctions() const;
			std::vector<FileVariable*> GetProtectedMemberVariables() const;
			
			std::vector<FileSection*> GetPublicMembers() const;
			std::vector<FileFunctionSection*> GetPublicMemberFunctions() const;
			std::vector<FileVariable*> GetPublicMemberVariables() const;

			void AddPrivateMember(FileVariable* member);
			void AddProtectedMember(FileVariable* member);
			void AddPublicMember(FileVariable* member);

			void AddPrivateMember(FileFunctionSection* memberFunction);
			void AddProtectedMember(FileFunctionSection* memberFunction);
			void AddPublicMember(FileFunctionSection* memberFunction);

			void AddPrivateMember(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType);
			void AddProtectedMember(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType);
			void AddPublicMember(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType);
			void AddPublicMember(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType, bool isVirtual);
			FileFunctionSection* GetCorrespondingVirtualFunction(const char* str);
			void AddPublicMember(const std::string& cs, const std::vector<FileVariable*>& args, FileVariableType* file_variable, bool is_virtual, bool _override);
			std::vector<FileFunctionSection*> GetPrivateVirtualMemberFunctions();
			std::vector<FileFunctionSection*> GetProtectedVirtualMemberFunctions();
			std::vector<FileFunctionSection*> GetPublicVirtualMemberFunctions();
			std::vector<deamer::FileFunctionSection*> GetVirtualMemberFunctions();
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILECLASSSECTION_H