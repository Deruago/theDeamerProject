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

#include "Deamer/FileProcessor/FileReadPasses/FileReadAddBracketsAtSameLevelIndentedLines.h"

deamer::FileReadAddBracketsAtSameLevelIndentedLines::FileReadAddBracketsAtSameLevelIndentedLines(
	const std::string& illegal_chars) : FileReadMidPass(illegal_chars)
{
}

deamer::FileReadAddBracketsAtSameLevelIndentedLines::FileReadAddBracketsAtSameLevelIndentedLines(
	const std::string& illegal_characters, const std::string& illegal_block) : FileReadMidPass(illegal_characters, illegal_block)
{
}

std::vector<std::string> deamer::FileReadAddBracketsAtSameLevelIndentedLines::ProcessLines(
	std::vector<std::string>& lines) const
{
	for (unsigned i = 0; i < lines.size() - 1; i++)
	{
		ConvertIndentationToBracketsUsingTheseLines(i, i + 1, lines);
	}
	return lines;
}

unsigned deamer::FileReadAddBracketsAtSameLevelIndentedLines::GetLastLineIndentDepthIgnoringIndentedSubBlockLines(const unsigned current_line_index, std::vector<std::string>& lines) const
{
	const unsigned current_line_indent_depth = GetAmountOfIndentsInLine(lines[current_line_index]);
	unsigned previous_line_peek_count = 1;
	unsigned last_line_indent_depth;

	if (current_line_index == 0)
		last_line_indent_depth = 0;
	else
		last_line_indent_depth = GetAmountOfIndentsInLine(lines[current_line_index - previous_line_peek_count]);
	
	while(last_line_indent_depth > current_line_indent_depth)
	{
		previous_line_peek_count++;
		last_line_indent_depth = GetAmountOfIndentsInLine(lines[current_line_index - previous_line_peek_count]);		
	}
	
	return last_line_indent_depth;
}

void deamer::FileReadAddBracketsAtSameLevelIndentedLines::ConvertIndentationToBracketsUsingTheseLines(
	const unsigned current_line_index, const unsigned next_line_index, std::vector<std::string>& lines) const
{
	const unsigned last_line_indent_depth = GetLastLineIndentDepthIgnoringIndentedSubBlockLines(current_line_index, lines);
	const unsigned current_line_indent_depth = GetAmountOfIndentsInLine(lines[current_line_index]);
	const unsigned next_line_indent_depth = GetAmountOfIndentsInLine(lines[next_line_index]);

	if ((next_line_indent_depth <= current_line_indent_depth && current_line_indent_depth >= last_line_indent_depth) && LineIsValid(lines[current_line_index]) && BlockIsValidWhereThisLineIsIn(lines, current_line_index))
		AddOpeningAndClosingBracketsAtEndOfLine(lines[current_line_index]);
}

void deamer::FileReadAddBracketsAtSameLevelIndentedLines::AddOpeningAndClosingBracketsAtEndOfLine(
	std::string& current_line) const
{
	AddCharacterAtEndOfLine(current_line, '{', 1);
	AddCharacterAtEndOfLine(current_line, '}', 1);
}