#include "Deamer/FileBuilder/Types/FileIncludeSection.h"

deamer::FileIncludeSection::FileIncludeSection(std::string include, bool isSystem)
{
	if (isSystem)
	{
		output = "<" + include + ">";
	}
	else
	{
		output = "\"" + include + ".h\"";
	}
}

std::string deamer::FileIncludeSection::GetOutput()
{
	return "#include " + output;
}
