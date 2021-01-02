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