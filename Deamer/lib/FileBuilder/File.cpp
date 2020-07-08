/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/FileBuilder/File.h"

deamer::File::File(std::string fileName, std::string fileExtension)
{
	FileName = fileName;
	FileExtension = fileExtension;
}

std::string deamer::File::GetFileName() const
{
	return FileName;
}

std::string deamer::File::GetFileExtension() const
{
	return FileExtension;
}
