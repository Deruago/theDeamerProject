/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -July 2020 Thimo B�hmer
 */

#ifndef DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONSECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONSECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include "Deamer/FileBuilder/Types/FileFunctionPrototypeSection.h"
#include "Deamer/FileBuilder/Types/FileBlockSection.h"

namespace deamer
{
	class FileFunctionSection : public FileSection
	{
		private:
			FileFunctionPrototypeSection* functionPrototype;
		protected:
		public:
			FileFunctionSection(FileFunctionPrototypeSection* functionPrototype);
			FileFunctionSection(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope);
			FileFunctionSection(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope, bool isMember);
			~FileFunctionSection() = default;
			void SetFunctionBlock(FileBlockSection* block); // Used to define the logic of the function
			std::string GetOutput() override;
			std::string GetFunctionPrototypeOutput(bool fullPath) const;
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONSECTION_H