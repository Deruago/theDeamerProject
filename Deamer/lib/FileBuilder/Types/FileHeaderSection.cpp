/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/FileBuilder/Types/FileHeaderSection.h"
#include "Deamer/FileBuilder/Types/FileHeaderGuardSection.h"

deamer::FileHeaderSection::FileHeaderSection(Directory* dir, File* file) : FileSection(dir, file)
{
	headerGuard = AddHeaderGuard(GetDirectory(), GetFile());
}

deamer::FileHeaderGuardSection* deamer::FileHeaderSection::AddHeaderGuard(Directory* directory, File* file)
{
	return new FileHeaderGuardSection(directory, file);
}

std::string deamer::FileHeaderSection::GetOutput()
{
	StringBuilder headerFile;
	headerFile.Add(headerGuard->GetHeaderGuardBegin());


	
	headerFile.Add(headerGuard->GetHeaderGuardEnd());
	return headerFile.GetOutput();
}
