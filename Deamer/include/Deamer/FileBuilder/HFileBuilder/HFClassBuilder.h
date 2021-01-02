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

#ifndef DEAMER_FILEBUILDER_HFBUILDER_HFCLASSBUILDER_H
#define DEAMER_FILEBUILDER_HFBUILDER_HFCLASSBUILDER_H
#include "Deamer/FileBuilder/FileBuilder.h"
#include <vector>
#include <string>


#include "Deamer/FileBuilder/Types/FileClassSection.h"
#include "Deamer/FileBuilder/Types/FileHeaderSection.h"

namespace deamer
{
	class FileFunctionSection;
	class FileVariable;

	class HFClassBuilder : public FileBuilder
	{
	private:
		FileHeaderSection* headerSection;
		FileClassSection* _class;
		bool isIncludeSystemHeader(const std::string& cs) const;
	public:
		HFClassBuilder(Directory* directory, File* file, FileNamespaceSection* scope, std::vector<FileClassSection*> superClasses);
		HFClassBuilder(std::vector<std::string> directories, std::string fileName, FileNamespaceSection* scope, std::vector<FileClassSection*> superClasses);
		HFClassBuilder(std::vector<std::string> directories, std::string fileName, FileNamespaceSection* scope);
		HFClassBuilder(std::vector<std::string> directories, std::string fileName);
		~HFClassBuilder();
		void AddInclude(std::string include) const;
		void AddInclude(std::string include, bool is_system) const;
		
		void AddFunction(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType) const; // standard public
		void AddFunction(std::string functionName, std::vector<FileVariable*> args, const FileVariableType* returnType) const; // standard public
		void AddFunctionPrivate(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType) const;
		void AddFunctionProtected(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType) const;
		void AddFunctionPublic(std::string functionName, std::vector<FileVariable*> args, FileVariableType* returnType) const;

		
		void AddMember(FileVariable* variable) const; // standard private
		void AddMemberPrivate(FileVariable* variable) const;
		void AddMemberProtected(FileVariable* variable) const;
		void AddMemberPublic(FileVariable* variable) const;
		
		std::string GetDefinition() const;
		std::string GetImplementation() const;
		std::string GetOutput() const override; // returns definition
		FileClassSection* GetClass();
		void AddFunction(const char* str) const;
	};
}

#endif //DEAMER_FILEBUILDER_HFBUILDER_HFCLASSBUILDER_H