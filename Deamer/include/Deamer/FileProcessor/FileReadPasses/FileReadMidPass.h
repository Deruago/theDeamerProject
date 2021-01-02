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

#ifndef DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADMIDPASS_H
#define DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADMIDPASS_H
#include <fstream>
#include <vector>

namespace deamer
{
	class FileReadMidPass
	{
	public:
		FileReadMidPass() = default;
		FileReadMidPass(const std::string& illegal_characters);
		FileReadMidPass(const std::string& illegal_characters, const std::string& illegal_block);
		virtual ~FileReadMidPass() = default;
		virtual std::vector<std::string> ProcessLines(std::vector<std::string>& input_file) const = 0;
	protected:
		void AddCharacterInFrontOfLine(std::string& line, const unsigned amount, const char character) const;
		void AddCharacterAtEndOfLine(std::string& line, const char character, const unsigned amount) const;
		virtual bool LineIsValid(const std::string& line) const;
		virtual bool LineIsValid(const std::string& line, const std::string& illegal_characters) const;
		virtual bool BlockIsValidWhereThisLineIsIn(const std::vector<std::string>& lines, const unsigned line_index) const;
		bool IsCharacterIllegal(char character) const;
		bool IsCharacterIllegal(const char character, const std::string& illegal_characters) const;

		unsigned GetAmountOfIndentsInLine(const std::string& line) const;
	private:
		std::string illegal_characters_;
		std::string illegal_blocks_;
	};
}

#endif //DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADMIDPASS_H