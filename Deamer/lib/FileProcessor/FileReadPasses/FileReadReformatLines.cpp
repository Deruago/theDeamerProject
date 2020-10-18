/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -October 2020 Thimo Böhmer
 */

#include "Deamer/FileProcessor/FileReadPasses/FileReadReformatLines.h"

#include <iostream>

std::vector<std::string> deamer::FileReadReformatLines::ProcessLines(std::vector<std::string>& lines) const
{
	std::vector<std::string> newLines;
	std::string currentLine;
	bool newLineDetected = false;
	
	for (unsigned i = 0; i < lines.size() - 1; i++)
	{
		const std::string currentOldLine = lines[i];
		for (const char currentCharacter : currentOldLine)
		{
			if (currentCharacter == '\n')
				newLineDetected = true;

			currentLine += currentCharacter;

			if (newLineDetected)
			{
				newLines.push_back(currentLine);
				ResetLineInformation(currentLine, newLineDetected);
			}
		}
	}
	if (!currentLine.empty())
		newLines.push_back(currentLine + "\n");
	
	return newLines;
}

void deamer::FileReadReformatLines::AddCharacterToLine(std::string& line, const char newCharacter) const
{
	line += newCharacter;
}

void deamer::FileReadReformatLines::ResetLineInformation(std::string& line, bool& newLineDetected) const
{
	line = "";
	newLineDetected = false;
}
