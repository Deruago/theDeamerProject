#include "Deamer/FileBuilder/FileVariable.h"
#include "Deamer/StringBuilder/StringBuilder.h"

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
