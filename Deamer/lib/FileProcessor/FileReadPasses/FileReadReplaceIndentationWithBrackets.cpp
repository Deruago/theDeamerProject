/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
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
