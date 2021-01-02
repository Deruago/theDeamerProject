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

#include "Deamer/FileBuilder/FileVariable.h"
#include "Deamer/FileBuilder/FileVariableType.h"
#include "Deamer/StringBuilder/StringBuilder.h"
#include <string>

deamer::FileVariable::FileVariable(FileVariableType* varType, std::string varName, bool isMember = false)
{
	variableType = varType;
	variableName = varName;
	_is_member = isMember;
}

std::string deamer::FileVariable::GetOutput() const
{
	StringBuilder stringBuilder;
	AddOutputTypePath(&stringBuilder);
	AddVariableName(&stringBuilder);
	return stringBuilder.GetOutputIgnoreNewLine();
}

void deamer::FileVariable::AddOutputTypePath(StringBuilder* stringBuilder) const
{
	if (variableType != nullptr)
	{
		stringBuilder->Add(variableType->GetOutputType());
		if (_is_member)
		{
			stringBuilder->Add("::");
		}
		else
		{
			stringBuilder->Add(" ");
		}
	}
	else
	{
		stringBuilder->Add(" ");
	}
}

void deamer::FileVariable::AddVariableName(StringBuilder* stringBuilder) const
{
	stringBuilder->Add(GetVariableName());
}

std::string deamer::FileVariable::GetVariableName() const
{
	return variableName;
}
