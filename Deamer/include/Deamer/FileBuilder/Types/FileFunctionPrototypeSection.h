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

#ifndef DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONPROTOTYPESECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONPROTOTYPESECTION_H
#include "Deamer/FileBuilder/FileSection.h"

namespace deamer
{
	class StringBuilder;
	class FileVariableType;
	class FileVariable;

	class FileFunctionPrototypeSection : public FileSection
	{
		private:
			FileVariable* Function;
			std::vector<FileVariable*> FunctionArguments;
			FileVariableType* ReturnType;
			bool _is_virtual;
			bool _override;

			void AddReturnType(StringBuilder* stringBuilder) const;
			void AddFunctionName(StringBuilder* stringBuilder) const;
			void AddFunctionArgument(StringBuilder* stringBuilder, FileVariable* argument);
			void AddFunctionArguments(StringBuilder* stringBuilder);
			void AddFunctionArgumentsToStringBuilder(StringBuilder* stringBuilder);
			std::string GetFullFunctionName() const; // Returns the full path to the variable.
		protected:
		public:
			FileFunctionPrototypeSection(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope);
			FileFunctionPrototypeSection(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope, bool isMember);
			FileFunctionPrototypeSection(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope, bool isMember, bool isVirtual);
			FileFunctionPrototypeSection(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope, bool isMember, bool isVirtual, bool _override);
			bool IsVirtual() const;
			~FileFunctionPrototypeSection();
			std::string GetOutput() override;
			std::string GetOutputWithoutFullDeclaration();
			std::string GetFunctionName() const; // Returns only the function name
			std::vector<FileVariable*> GetFunctionArgs() const;
			FileVariableType* GetReturnType() const;
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONPROTOTYPESECTION_H
