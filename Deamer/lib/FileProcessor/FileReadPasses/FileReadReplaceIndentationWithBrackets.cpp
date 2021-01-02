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

#include "Deamer/FileProcessor/FileReadPasses/FileReadReplaceIndentationWithBrackets.h"

deamer::FileReadReplaceIndentationWithBrackets::FileReadReplaceIndentationWithBrackets(const std::string& illegal_chars) : FileReadMidPass(illegal_chars)
{
}

deamer::FileReadReplaceIndentationWithBrackets::FileReadReplaceIndentationWithBrackets(
	const std::string& illegal_characters, const std::string& illegal_block) : FileReadMidPass(illegal_characters, illegal_block)
{
}

std::vector<std::string> deamer::FileReadReplaceIndentationWithBrackets::ProcessLines(std::vector<std::string>& lines) const
{
	for(unsigned i = 1; i < lines.size() - 1; i++)
	{
		ConvertIndentationToBracketsUsingTheseLines(lines[i - 1], lines[i]);
	}
	return lines;
}

void deamer::FileReadReplaceIndentationWithBrackets::ConvertIndentationToBracketsUsingTheseLines(
	std::string& last_line, std::string& current_line) const
{
	const unsigned current_line_indent_depth = GetAmountOfIndentsInLine(current_line);
	const unsigned last_line_indent_depth = GetAmountOfIndentsInLine(last_line);

	if (current_line_indent_depth > last_line_indent_depth && LineIsValid(current_line))
		AddOpeningBracketsInFrontOfLine(current_line, current_line_indent_depth - last_line_indent_depth);
	else if (current_line_indent_depth < last_line_indent_depth && LineIsValid(current_line))
		AddClosingBracketsInFrontOfLine(current_line, last_line_indent_depth - current_line_indent_depth);
}

void deamer::FileReadReplaceIndentationWithBrackets::AddOpeningBracketsInFrontOfLine(std::string& current_line,
	unsigned amount) const
{
	AddCharacterInFrontOfLine(current_line, amount, '{');
}

void deamer::FileReadReplaceIndentationWithBrackets::AddClosingBracketsInFrontOfLine(std::string& current_line,
	unsigned amount) const
{
	AddCharacterInFrontOfLine(current_line, amount, '}');
}
