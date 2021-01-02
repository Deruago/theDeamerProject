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

#ifndef DEAMER_FILEBUILDER_TYPES_FILEHEADERSECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEHEADERSECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include <vector>
#include <string>

namespace deamer
{
	class FileHeaderGuardSection;
	class Directory;
	class File;
	class FileClassSection;
	class FileFunctionSection;
	class FileFunctionPrototypeSection;
	class FileNamespaceSection;
	class FileVariable;
	class FileVariableType;
	class FileIncludeSection;
	
	class FileHeaderSection : public FileSection
	{
		private:
			FileHeaderGuardSection* AddHeaderGuard(Directory* directory, File* file);
			std::vector<FileIncludeSection*> includes;
			std::vector<FileClassSection*> classes;
			std::vector<FileFunctionSection*> functions;
		protected:
			FileHeaderGuardSection* headerGuard;
		public:
			FileHeaderSection(Directory* dir, File* file);
			~FileHeaderSection();
			FileNamespaceSection* AddNamespace(std::string namespaceName);
			void AddNamespace(FileNamespaceSection* namespaceSection);
			FileClassSection* AddClass(std::string className, std::vector<FileClassSection*> superClasses, FileNamespaceSection* scope);
			void AddClass(FileClassSection* classSection);
			FileFunctionSection* AddFunction(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType*
			                                 scope);
			FileFunctionSection* AddFunction(FileFunctionPrototypeSection* functionPrototype);
			void AddFunction(FileFunctionSection* functionSection);
			std::string GetOutput() override;
			void AddInclude(const std::string& cs, bool isSystem);
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEHEADERSECTION_H
