#include "Deamer/FileBuilder/FileVariableType.h"

deamer::FileVariableType::FileVariableType(FileVariableType* variableTypeSection)
{
	_variableTypeSection = variableTypeSection;
}

deamer::FileVariableType::FileVariableType()
{
	_variableTypeSection = nullptr;
}

deamer::FileVariableType* deamer::FileVariableType::GetFileVariableType() const
{
	return _variableTypeSection;
}
