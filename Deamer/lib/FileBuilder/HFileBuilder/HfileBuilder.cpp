#include "Deamer/FileBuilder/HFileBuilder/HFileBuilder.h"

deamer::HFileBuilder::HFileBuilder(Directory* directory, File* file) : FileBuilder(directory, file)
{
	headerSection = new FileHeaderSection(directory, file);
}

std::string deamer::HFileBuilder::GetOutput() const
{
	return headerSection->GetOutput();
}

deamer::FileHeaderSection* deamer::HFileBuilder::GetHeaderSection() const
{
	return headerSection;
}
