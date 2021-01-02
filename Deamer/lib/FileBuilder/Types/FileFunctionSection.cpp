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
	FileVariableType* returnType, FileVariableType* scope) : FileFunctionSection(functionName, functionArgs, returnType, scope, false, false)
{
}

deamer::FileFunctionSection::FileFunctionSection(std::string functionName, std::vector<FileVariable*> functionArgs,
	FileVariableType* returnType, FileVariableType* scope, bool isMember) : FileFunctionSection(functionName, functionArgs, returnType, scope, isMember, false)
{
}

deamer::FileFunctionSection::FileFunctionSection(const std::string& functionName, const std::vector<FileVariable*>& args,
	FileVariableType* returnType, FileVariableType* scope, bool isMember, bool is_virtual)
{
	functionPrototype = new FileFunctionPrototypeSection(functionName, args, returnType, scope, isMember, is_virtual);
}

deamer::FileFunctionSection::~FileFunctionSection()
{
	delete functionPrototype;
}

std::string deamer::FileFunctionSection::GetOutput()
{
	return "";
}

bool deamer::FileFunctionSection::IsVirtual() const
{
	return functionPrototype->IsVirtual();
}

std::string deamer::FileFunctionSection::GetFunctionPrototypeOutput(bool fullPath, bool instruction) const
{
	std::string tmpString;
	if (fullPath)
	{
		tmpString = functionPrototype->GetOutput();
	}
	else
	{
		tmpString = functionPrototype->GetOutputWithoutFullDeclaration();
	}

	if (instruction)
		tmpString += ";";
	return tmpString;
}

std::string deamer::FileFunctionSection::GetFunctionName() const
{
	return functionPrototype->GetFunctionName();
}

std::vector<deamer::FileVariable*> deamer::FileFunctionSection::GetFunctionArgs() const
{
	return functionPrototype->GetFunctionArgs();
}

deamer::FileVariableType* deamer::FileFunctionSection::GetReturnType() const
{
	return functionPrototype->GetReturnType();
}
