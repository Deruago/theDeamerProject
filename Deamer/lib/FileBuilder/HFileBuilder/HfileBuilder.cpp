#include "Deamer/FileBuilder/HFileBuilder/HFileBuilder.h"
#include "Deamer/FileBuilder/Types/FileHeaderSection.h"
#include "Deamer/FileBuilder/Directory.h"
#include "Deamer/FileBuilder/File.h"
#include <vector>
#include <string>

deamer::HFileBuilder::HFileBuilder(Directory* directory, File* file) : FileBuilder(directory, file)
{
	headerSection = new FileHeaderSection(directory, file);
}

deamer::HFileBuilder::HFileBuilder(std::vector<std::string> directories, std::string fileName, std::string extension) : FileBuilder(new Directory(directories), new File(fileName, extension))
{
	headerSection = new FileHeaderSection(_Directory, _File);
}

std::string deamer::HFileBuilder::GetOutput() const
{
	return headerSection->GetOutput();
}

deamer::FileHeaderSection* deamer::HFileBuilder::GetHeaderSection() const
{
	return headerSection;
}

void deamer::HFileBuilder::AddInclude(std::string _path) const
{
	headerSection->AddInclude(_path, false);
}
