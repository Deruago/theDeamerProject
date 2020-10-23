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
#include "Deamer/FileProcessor/FileReadPasses/FileReadRemoveLinesStartingWithCharacter.h"
#include "Deamer/FileProcessor/FileReadPasses/FileReadAddBracketsAtSameLevelIndentedLines.h"
#include "Deamer/FileProcessor/FileReadPasses/FileReadReformatLines.h"
#include "Deamer/FileProcessor/FileReadPasses/FileReadReplaceCharactersWithString.h"
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
	const FileReadRemoveLinesStartingWithCharacter comment_cleaner("/");

	const FileReadReformatLines lineReformat;

	const FileReadReplaceIndentationWithBrackets indentation_to_brackets;
	const FileReadAddBracketsAtSameLevelIndentedLines brackets_at_same_level("", "");

	auto lines = input_cleaner.ProcessFile(read_in_file);
	//lines.push_back("/\r\n");
	lines.push_back("\r\n");
	lines = indentation_to_brackets.ProcessLines(lines);
	lines = brackets_at_same_level.ProcessLines(lines);

	lines = lineReformat.ProcessLines(lines);

	lines = comment_cleaner.ProcessLines(lines);

	/*const std::string tmpLine = lines[lines.size() - 1];
	std::string newTMPLine;
	for (const char tmpChar : tmpLine)
	{
		if (tmpChar == '/')
		{
			newTMPLine += '\n';
			break;
		}

		newTMPLine += tmpChar;
	}

	lines[lines.size() - 1] = newTMPLine;*/

	// Deletes everything after comment in following situation:
	// }/coment
	std::vector<std::string> newLines;
	for (unsigned i = 0; i < lines.size(); i++)
	{
		bool LEFT_BRACKET_FOUND = false;
		unsigned CharCount = 0;
		std::string newTMPLine;
		for (const char character : lines[i])
		{
			CharCount++;
			if (LEFT_BRACKET_FOUND && character == '/' && CharCount == 2)
			{
				newTMPLine += "\n";
				break;
			}
			if (character == '}')
				LEFT_BRACKET_FOUND = true;
			else
				LEFT_BRACKET_FOUND = false;

			newTMPLine += character;
		}
		newLines.push_back(newTMPLine);
	}
	lines = newLines;

	std::string tmpStr = lines[lines.size() - 1];
	if (tmpStr.size() >= 4)
	{
		std::cout << tmpStr << std::endl;
		if (*(tmpStr.end() - 4) == '{' &&
			*(tmpStr.end() - 3) == '}' &&
			*(tmpStr.end() - 2) == '/')
		{
			tmpStr.pop_back();
			tmpStr.pop_back();
			tmpStr.pop_back();
			tmpStr.pop_back();
			tmpStr.push_back('\n');
		}
		std::cout << tmpStr << std::endl;
		lines[lines.size() - 1] = tmpStr;
	}
	
	
	for(const std::string& line : lines)
	{
		output += line;
	}
	
	return output;
}