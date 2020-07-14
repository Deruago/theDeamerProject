/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/FileBuilder/Types/FileFunctionSection.h"
#include "Deamer/FileBuilder/Types/FileFunctionPrototypeSection.h"
#include "Deamer/FileBuilder/FileVariableType.h"
#include "Deamer/FileBuilder/FileVariable.h"
#include <vector>
#include <string>

deamer::FileFunctionSection::FileFunctionSection(FileFunctionPrototypeSection* functionPrototype)
{
	FileFunctionSection::functionPrototype = functionPrototype;
}

deamer::FileFunctionSection::FileFunctionSection(std::string functionName, std::vector<FileVariable*> functionArgs,
	FileVariableType* returnType, FileVariableType* scope)
{
	functionPrototype = new FileFunctionPrototypeSection(functionName, functionArgs, returnType, scope);
}

deamer::FileFunctionSection::FileFunctionSection(std::string functionName, std::vector<FileVariable*> functionArgs,
	FileVariableType* returnType, FileVariableType* scope, bool isMember)
{
	functionPrototype = new FileFunctionPrototypeSection(functionName, functionArgs, returnType, scope, isMember);
}

std::string deamer::FileFunctionSection::GetOutput()
{
	return "";
}

std::string deamer::FileFunctionSection::GetFunctionPrototypeOutput(bool fullPath) const
{
	if (fullPath)
	{
		return functionPrototype->GetOutput();
	}
	else
	{
		return functionPrototype->GetOutputWithoutFullDeclaration();
	}
}