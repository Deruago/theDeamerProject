/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/FileProcessor/FileReadProcessor.h"
#include "Deamer/FileProcessor/FileReadPasses/FileReadRemoveUnusedText.h"
#include "Deamer/FileProcessor/FileReadPasses/FileReadReplaceIndentationWithBrackets.h"
#include "Deamer/FileProcessor/FileReadPasses/FileReadAddBracketsAtSameLevelIndentedLines.h"
#include <fstream>
#include <iostream>


deamer::FileReadProcessor::FileReadProcessor(FileRead_Passes file_read_passes)
{
	file_read_passes_ = file_read_passes;
}

std::string deamer::FileReadProcessor::ReadFile(const std::string& file_location)
{
	std::string output;
	std::ifstream read_in_file(file_location);
	const FileReadRemoveUnusedText input_cleaner;
	const FileReadReplaceIndentationWithBrackets indentation_to_brackets;
	const FileReadAddBracketsAtSameLevelIndentedLines brackets_at_same_level(":/", ":");

	auto lines = input_cleaner.ProcessFile(read_in_file);
	lines = indentation_to_brackets.ProcessLines(lines);
	lines = brackets_at_same_level.ProcessLines(lines);
	for(const std::string& line : lines)
	{
		output += line;
	}
	
	return output;
}