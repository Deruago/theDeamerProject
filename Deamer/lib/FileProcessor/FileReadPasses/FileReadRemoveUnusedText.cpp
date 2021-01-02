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

#include "Deamer/FileProcessor/FileReadPasses/FileReadRemoveUnusedText.h"

std::vector<std::string> deamer::FileReadRemoveUnusedText::ProcessFile(std::ifstream& input_file) const
{
	bool line_contains_only_ignored_characters = true;

	std::vector<std::string> output_lines;
	std::string current_line;
	
	char c;
	while(input_file.get(c))
	{
		ProcessCharacter(c, line_contains_only_ignored_characters, current_line, output_lines);
	}
	FinishLine(line_contains_only_ignored_characters, current_line, output_lines);

	return output_lines;
}

void deamer::FileReadRemoveUnusedText::ProcessCharacter(const char character, bool& line_contains_only_ignored_characters,
	std::string& current_line, std::vector<std::string>& output_lines) const
{
	switch (character)
	{
	case '\t':
		AddCharacterToCurrentLine(current_line, character);
		break;
	case '\n':
		AddCharacterToCurrentLine(current_line, character);
		FinishLine(line_contains_only_ignored_characters, current_line, output_lines);
		break;
	case '\r':
		break;
	case '\b':
		break;
	case '\f':
		break;
	case '\v':
		break;
	default: //any normal character
		AddCharacterToCurrentLine(current_line, character);
		line_contains_only_ignored_characters = false;
		break;
	}
}

void deamer::FileReadRemoveUnusedText::AddCharacterToCurrentLine(std::string& current_line, const char character) const
{
	current_line += character;
}

void deamer::FileReadRemoveUnusedText::FinishLine(bool& line_contains_only_ignored_characters, std::string& current_line, std::vector<std::string>& output_lines) const
{
	if (!line_contains_only_ignored_characters)
		output_lines.push_back(current_line);
	ResetLineInformation(current_line, line_contains_only_ignored_characters);
}

void deamer::FileReadRemoveUnusedText::ResetLineInformation(std::string& current_line, bool& line_contains_only_ignored_characters) const
{
	current_line = "";
	line_contains_only_ignored_characters = true;
}
