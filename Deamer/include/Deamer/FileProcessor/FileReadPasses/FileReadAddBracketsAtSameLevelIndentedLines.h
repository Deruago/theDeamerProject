/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADADDBRACKETSATSAMELEVELINDENTEDLINES_H
#define DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADADDBRACKETSATSAMELEVELINDENTEDLINES_H

#include "Deamer/FileProcessor/FileReadPasses/FileReadMidPass.h"
#include <fstream>
#include <vector>

namespace deamer
{
	class FileReadAddBracketsAtSameLevelIndentedLines : FileReadMidPass
	{
	private:
		void AddOpeningAndClosingBracketsAtEndOfLine(std::string& current_line) const;
	public:
		FileReadAddBracketsAtSameLevelIndentedLines() = default;
		FileReadAddBracketsAtSameLevelIndentedLines(const std::string& illegal_chars);
		FileReadAddBracketsAtSameLevelIndentedLines(const std::string& illegal_characters, const std::string& illegal_block);

		std::vector<std::string> ProcessLines(std::vector<std::string>& lines) const override;
		unsigned GetLastLineIndentDepthIgnoringIndentedSubBlockLines(const unsigned current_line_index, std::vector<std::string>& lines) const;
		void ConvertIndentationToBracketsUsingTheseLines(const unsigned current_line_index, const unsigned next_line_index, std::vector<std::string>& lines) const;
	};
}

#endif //DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADADDBRACKETSATSAMELEVELINDENTEDLINES_H