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
