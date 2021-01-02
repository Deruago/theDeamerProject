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