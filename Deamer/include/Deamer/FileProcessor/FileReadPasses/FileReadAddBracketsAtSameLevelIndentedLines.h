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