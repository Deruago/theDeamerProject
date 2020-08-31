/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
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