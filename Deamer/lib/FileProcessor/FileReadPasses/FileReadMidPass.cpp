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

#include "Deamer/FileProcessor/FileReadPasses/FileReadMidPass.h"

deamer::FileReadMidPass::FileReadMidPass(const std::string& illegal_characters)
{
	illegal_characters_ = illegal_characters;
}

deamer::FileReadMidPass::FileReadMidPass(const std::string& illegal_characters, const std::string& illegal_block)
{
	illegal_characters_ = illegal_characters;
	illegal_blocks_ = illegal_block;
}

void deamer::FileReadMidPass::AddCharacterInFrontOfLine(std::string& line, const unsigned amount,
                                                        const char character) const
{
	std::string tmp_front;
	for(unsigned i = 0; i < amount; i++)
	{
		tmp_front += character;
	}
	line = tmp_front + line;
}

void deamer::FileReadMidPass::AddCharacterAtEndOfLine(std::string& line, const char character,
	const unsigned amount) const
{
	std::string tmp_front;
	for (unsigned i = 0; i < amount; i++)
	{
		tmp_front += character;
	}
	line.insert(line.size() - 1, tmp_front);
}

bool deamer::FileReadMidPass::BlockIsValidWhereThisLineIsIn(const std::vector<std::string>& lines,
                                                            const unsigned line_index) const
{
	unsigned last_line_depth = GetAmountOfIndentsInLine(lines[line_index]);
	unsigned tmp_line_index = line_index;
	if (last_line_depth == 0)
		return LineIsValid(lines[tmp_line_index]);
	while(last_line_depth > 0 && tmp_line_index >= 0)
	{
		const unsigned line_depth = GetAmountOfIndentsInLine(lines[tmp_line_index]);
		if (line_depth < last_line_depth)
		{
			last_line_depth = line_depth;
			if (!LineIsValid(lines[tmp_line_index], illegal_blocks_))
			{
				return false;
			}
		}
		if (line_depth != 0)
		{
			tmp_line_index--;
		}
	}

	return LineIsValid(lines[tmp_line_index], illegal_blocks_);
}

bool deamer::FileReadMidPass::LineIsValid(const std::string& line) const
{
	return LineIsValid(line, illegal_characters_);
}

bool deamer::FileReadMidPass::LineIsValid(const std::string& line, const std::string& illegal_characters) const
{
	for (const char character : line)
	{
		if (IsCharacterIllegal(character, illegal_characters))
			return false;
	}
	return true;
}

bool deamer::FileReadMidPass::IsCharacterIllegal(const char character) const
{
	return IsCharacterIllegal(character, illegal_characters_);
}

bool deamer::FileReadMidPass::IsCharacterIllegal(const char character, const std::string& illegal_characters) const
{
	for (const char illegal_character : illegal_characters)
	{
		if (character == illegal_character)
			return true;
	}
	return false;
}


unsigned deamer::FileReadMidPass::GetAmountOfIndentsInLine(const std::string& line) const
{
	unsigned depth = 0;
	for (const char character : line)
	{
		if (character == '\t')
			depth++;
	}
	return depth;
}
