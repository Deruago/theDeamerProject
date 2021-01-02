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
	std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope, bool isMember) : FileFunctionPrototypeSection(functionName, functionArgs, returnType,  scope, isMember, false)
{
}

deamer::FileFunctionPrototypeSection::FileFunctionPrototypeSection(std::string functionName,
	std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope, bool isMember,
	bool isVirtual) : FileFunctionPrototypeSection(functionName, functionArgs, returnType, scope, isMember, isVirtual, false)
{
}

deamer::FileFunctionPrototypeSection::FileFunctionPrototypeSection(std::string functionName,
	std::vector<FileVariable*> functionArgs, FileVariableType* returnType, FileVariableType* scope, bool isMember,
	bool isVirtual, bool _override)
{
	FunctionArguments = functionArgs;
	ReturnType = returnType;
	Function = new FileVariable(scope, functionName, isMember);
	_is_virtual = isVirtual;
	FileFunctionPrototypeSection::_override = _override;
}

bool deamer::FileFunctionPrototypeSection::IsVirtual() const
{
	return _is_virtual;
}

deamer::FileFunctionPrototypeSection::~FileFunctionPrototypeSection()
{
	delete_members(FunctionArguments);
}

std::string deamer::FileFunctionPrototypeSection::GetOutput()
{
	StringBuilder stringBuilder;
	if (_is_virtual)
		stringBuilder.Add("virtual ");
	AddReturnType(&stringBuilder);
	AddFunctionName(&stringBuilder);
	AddFunctionArgumentsToStringBuilder(&stringBuilder);
	if (_override)
		stringBuilder.Add(" override");
	return stringBuilder.GetOutputIgnoreNewLine();
}

std::string deamer::FileFunctionPrototypeSection::GetOutputWithoutFullDeclaration()
{
	StringBuilder stringBuilder;
	if (_is_virtual)
		stringBuilder.Add("virtual ");
	AddReturnType(&stringBuilder);
	stringBuilder.Add(GetFunctionName());
	AddFunctionArgumentsToStringBuilder(&stringBuilder);
	if (_override)
		stringBuilder.Add(" override");
	return stringBuilder.GetOutputIgnoreNewLine();
}

std::string deamer::FileFunctionPrototypeSection::GetFunctionName() const
{
	return Function->GetVariableName();
}

std::vector<deamer::FileVariable*> deamer::FileFunctionPrototypeSection::GetFunctionArgs() const
{
	return FunctionArguments;
}

deamer::FileVariableType* deamer::FileFunctionPrototypeSection::GetReturnType() const
{
	return ReturnType;
}

std::string deamer::FileFunctionPrototypeSection::GetFullFunctionName() const
{
	return Function->GetOutput();
}

void deamer::FileFunctionPrototypeSection::AddReturnType(StringBuilder* stringBuilder) const
{
	stringBuilder->Add(ReturnType->GetOutputType());
	stringBuilder->Add(" ");
}

void deamer::FileFunctionPrototypeSection::AddFunctionName(StringBuilder* stringBuilder) const
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
