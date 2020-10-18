/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -October 2020 Thimo Böhmer
 */

#include "Deamer/FileProcessor/FileReadPasses/FileReadReplaceCharactersWithString.h"

deamer::FileReadReplaceCharactersWithString::FileReadReplaceCharactersWithString(
	const std::string& characters_to_replace, const std::string& inserted_string)
{
	characters_to_replace_ = characters_to_replace;
	inserted_string_ = inserted_string;
}

std::vector<std::string> deamer::FileReadReplaceCharactersWithString::ProcessLines(std::vector<std::string>& lines) const
{
	std::vector<std::string> newLines;
	for (unsigned i = 0; i < lines.size() - 1; i++)
	{
		const std::string newLine = createUpdatedLine(lines[i]);
		newLines.push_back(newLine);
	}
	return newLines;
}

std::string deamer::FileReadReplaceCharactersWithString::createUpdatedLine(const std::string& oldLine) const
{
	std::string newLine;
	for (const char character : oldLine)
	{
		if (shouldCharacterBeReplaced(character))
		{
			newLine += inserted_string_;
		}
		else
		{
			newLine += character;
		}
	}
	return newLine;
}

bool deamer::FileReadReplaceCharactersWithString::shouldCharacterBeReplaced(const char character) const
{
	for (const char illegal_character : characters_to_replace_)
	{
		if (character == illegal_character)
		{
			return true;
		}
	}
	return false;
}
