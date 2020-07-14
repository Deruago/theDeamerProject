/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/FileBuilder/Types/FileFunctionPrototypeSection.h"
#include "Deamer/FileBuilder/FileVariableType.h"
#include "Deamer/FileBuilder/FileVariable.h"
#include "Deamer/StringBuilder/StringBuilder.h"
#include <vector>
#include <string>

deamer::FileFunctionPrototypeSection::FileFunctionPrototypeSection(std::string functionName,
	std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope) : FileFunctionPrototypeSection(functionName, functionArgs, returnType, scope, true)
{
}

deamer::FileFunctionPrototypeSection::FileFunctionPrototypeSection(std::string functionName,
	std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope, bool isMember)
{
	FunctionArguments = functionArgs;
	ReturnType = returnType;
	Function = new FileVariable(scope, functionName, isMember);
}

std::string deamer::FileFunctionPrototypeSection::GetOutput()
{
	StringBuilder stringBuilder;
	AddReturnType(&stringBuilder);
	AddFunctionName(&stringBuilder);
	AddFunctionArgumentsToStringBuilder(&stringBuilder);
	return stringBuilder.GetOutputIgnoreNewLine();
}

std::string deamer::FileFunctionPrototypeSection::GetOutputWithoutFullDeclaration()
{
	StringBuilder stringBuilder;
	AddReturnType(&stringBuilder);
	stringBuilder.Add(GetFunctionName());
	AddFunctionArgumentsToStringBuilder(&stringBuilder);
	return stringBuilder.GetOutputIgnoreNewLine();
}

std::string deamer::FileFunctionPrototypeSection::GetFunctionName() const
{
	return Function->GetVariableName();
}

std::string deamer::FileFunctionPrototypeSection::GetFullFunctionName() const
{
	return Function->GetOutput();
}

void deamer::FileFunctionPrototypeSection::AddReturnType(StringBuilder* stringBuilder)
{
	stringBuilder->Add(ReturnType->GetOutputType());
	stringBuilder->Add(" ");
}

void deamer::FileFunctionPrototypeSection::AddFunctionName(StringBuilder* stringBuilder)
{
	stringBuilder->Add(GetFullFunctionName());
}

void deamer::FileFunctionPrototypeSection::AddFunctionArgumentsToStringBuilder(StringBuilder* stringBuilder)
{
	stringBuilder->Add("(");
	if (!FunctionArguments.empty())
	{
		AddFunctionArguments(stringBuilder);
	}
	stringBuilder->Add(")");
}

void deamer::FileFunctionPrototypeSection::AddFunctionArguments(StringBuilder* stringBuilder)
{
	for (unsigned int i = 0; i < FunctionArguments.size(); i++)
	{
		AddFunctionArgument(stringBuilder, FunctionArguments[i]);
		if (i < FunctionArguments.size() - 1)
		{
			stringBuilder->Add(", ");
		}
	}
}

void deamer::FileFunctionPrototypeSection::AddFunctionArgument(StringBuilder* stringBuilder, FileVariable* argument)
{
	stringBuilder->Add(argument->GetOutput());
}
