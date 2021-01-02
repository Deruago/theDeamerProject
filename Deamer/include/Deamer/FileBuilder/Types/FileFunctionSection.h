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

#ifndef DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONSECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONSECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include "FileClassSection.h"

namespace deamer
{
	class FileFunctionPrototypeSection;
	class FileVariable;
	class FileVariableType;
	class FileBlockSection;
	
	class FileFunctionSection : public FileSection
	{
		private:
			FileFunctionPrototypeSection* functionPrototype;
		protected:
		public:
			FileFunctionSection(FileFunctionPrototypeSection* functionPrototype);
			FileFunctionSection(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope);
			FileFunctionSection(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope, bool isMember);
			FileFunctionSection(const std::string& functionName, const std::vector<FileVariable*>& args,
			                    FileVariableType* returnType, FileVariableType* scope, bool isMember, bool is_virtual);
			~FileFunctionSection();
			void SetFunctionBlock(FileBlockSection* block); // Used to define the logic of the function
			std::string GetOutput() override;
			bool IsVirtual() const;
			std::string GetFunctionPrototypeOutput(bool fullPath, bool instruction) const;
			std::string GetFunctionName() const;
			std::vector<FileVariable*> GetFunctionArgs() const;
			FileVariableType* GetReturnType() const;
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONSECTION_H