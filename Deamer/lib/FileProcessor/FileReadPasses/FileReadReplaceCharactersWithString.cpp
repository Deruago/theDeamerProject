/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
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
