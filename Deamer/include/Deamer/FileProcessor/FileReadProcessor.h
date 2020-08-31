/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEPROCESSOR_FILEREADPROCESSOR_H
#define DEAMER_FILEPROCESSOR_FILEREADPROCESSOR_H
#include "Deamer/Types/BitwiseEnum.h"
#include "Deamer/FileProcessor/FileRead_Passes.h"
#include <string>

/*
 * This class can be used to read in files and
 * process them using "passes". These passes modify partly
 * the input to make it easier to handle.
 *
 * This class focusses on simple changes.
 *
 * For example: converting indentation to curly bracket logic
 */

namespace deamer
{
	class FileReadProcessor
	{
	private:
		BitwiseEnum<FileRead_Passes> file_read_passes_;
	protected:
	public:
		FileReadProcessor() = default;
		FileReadProcessor(FileRead_Passes file_read_passes);
		std::string ReadFile(const std::string& file_location);
	};
}

#endif //DEAMER_FILEPROCESSOR_FILEREADPROCESSOR_H