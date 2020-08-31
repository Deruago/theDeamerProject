/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREPLACEINDENTATIONWITHBRACKETS_H
#define DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREPLACEINDENTATIONWITHBRACKETS_H

#include "Deamer/FileProcessor/FileReadPasses/FileReadMidPass.h"

namespace deamer
{
	class FileReadReplaceIndentationWithBrackets : FileReadMidPass
	{
	private:
	public:
		FileReadReplaceIndentationWithBrackets() = default;
		FileReadReplaceIndentationWithBrackets(const std::string& illegal_chars);
		FileReadReplaceIndentationWithBrackets(const std::string& illegal_characters, const std::string& illegal_block);

		void AddOpeningBracketsInFrontOfLine(std::string& current_line, unsigned amount) const;
		void AddClosingBracketsInFrontOfLine(std::string& current_line, unsigned amount) const;
		void ConvertIndentationToBracketsUsingTheseLines(std::string& last_line, std::string& current_line) const;
		std::vector<std::string> ProcessLines(std::vector<std::string>& lines) const override;
	};
}

#endif //DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREPLACEINDENTATIONWITHBRACKETS_H