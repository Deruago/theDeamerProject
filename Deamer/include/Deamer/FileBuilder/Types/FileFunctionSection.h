/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
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