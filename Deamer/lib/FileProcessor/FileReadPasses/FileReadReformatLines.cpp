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
