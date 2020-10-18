/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -October 2020 Thimo Böhmer
 */

#include "Deamer/FileProcessor/FileReadPasses/FileReadRemoveLinesStartingWithCharacter.h"

deamer::FileReadRemoveLinesStartingWithCharacter::FileReadRemoveLinesStartingWithCharacter(
	const std::string& illegal_characters)
{
	illegal_characters_ = illegal_characters;
}

std::vector<std::string> deamer::FileReadRemoveLinesStartingWithCharacter::ProcessLines(
	std::vector<std::string>& lines) const
{
	std::vector<std::string> newLines;
	for (auto currentLine : lines)
	{
		if (currentLine.empty())
			continue;
		
		if (!DoesLineStartWithIllegalCharacter(currentLine))
			newLines.push_back(currentLine);
	}
	
	return newLines;
}

bool deamer::FileReadRemoveLinesStartingWithCharacter::DoesLineStartWithIllegalCharacter(
	const std::string& line) const
{
	const char character = line[0];
	for (const char illegal_character : illegal_characters_)
	{
		if (character == illegal_character)
			return true;
	}
	return false;
}
