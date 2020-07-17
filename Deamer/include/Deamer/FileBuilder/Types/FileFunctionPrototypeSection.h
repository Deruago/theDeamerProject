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
