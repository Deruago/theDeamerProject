/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONPROTOTYPESECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONPROTOTYPESECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include "Deamer/FileBuilder/FileVariable.h"
#include "Deamer/FileBuilder/FileVariableType.h"

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

			void AddReturnType(StringBuilder* stringBuilder);
			void AddFunctionName(StringBuilder* stringBuilder);
			void AddFunctionArgument(StringBuilder* stringBuilder, FileVariable* argument);
			void AddFunctionArguments(StringBuilder* stringBuilder);
			void AddFunctionArgumentsToStringBuilder(StringBuilder* stringBuilder);
			std::string GetFunctionName() const; // Returns only the function name
			std::string GetFullFunctionName() const; // Returns the full path to the variable.
		protected:
		public:
			FileFunctionPrototypeSection(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope);
			FileFunctionPrototypeSection(std::string functionName, std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope, bool isMember);
			~FileFunctionPrototypeSection() = default;
			std::string GetOutput() override;
			std::string GetOutputWithoutFullDeclaration();
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEFUNCTIONPROTOTYPESECTION_H
