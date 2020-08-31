/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREMOVEUNUSEDTEXT_H
#define DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREMOVEUNUSEDTEXT_H

#include "Deamer/FileProcessor/FileReadPasses/FileReadPass.h"

namespace deamer
{
	class FileReadRemoveUnusedText : FileReadPass
	{
	private:
		void AddCharacterToCurrentLine(std::string& current_line, const char character) const;
		void FinishLine(bool& line_contains_only_ignored_characters, std::string& current_line, std::vector<std::string>& output_lines) const;
		void ResetLineInformation(std::string& current_line, bool& line_contains_only_ignored_characters) const;
	public:
		FileReadRemoveUnusedText() = default;
		std::vector<std::string> ProcessFile(std::ifstream& input_file) const override;
		void ProcessCharacter(const char character, bool& line_contains_only_ignored_characters, std::string& current_line, std::vector<std::string>&
		                      output_lines) const;
	};
}

#endif //DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREMOVEUNUSEDTEXT_H