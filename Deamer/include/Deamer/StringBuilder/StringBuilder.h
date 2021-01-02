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

#ifndef DEAMER_STRINGBUILDER_STRINGBUILDER_H
#define DEAMER_STRINGBUILDER_STRINGBUILDER_H
#include <vector>
#include <string>

namespace deamer
{
	class StringBuilder
	{
		private:
			bool doesOutputContainAmountLines(unsigned position) const;
			void CapPositionToOutputLineSize(unsigned* position) const;
			void CapPositionToOutputLineSize(unsigned* begin_postion, unsigned* end_position) const;
			void RemoveExtraLines(unsigned begin_postion, unsigned end_position);
			void CompressLines(unsigned beginPosition, unsigned endPosition);
			void CompressLinesIgnoreNewLines(unsigned beginPosition, unsigned endPosition);
			void AddLinesFromStringBuilderToOwnOutput(const StringBuilder string_builder);
			std::string makeLineLowerCase(const std::string line);
			std::string makeLineUpperCase(const std::string line);
			std::string createIndent(unsigned indent_size);
			std::string createIdentation(unsigned indentSize, unsigned indentDepth);
			std::string indentLine(std::string line, unsigned indent, unsigned depth);
		protected:
			std::vector<std::string> Output;
		public:
			StringBuilder() = default;
			~StringBuilder() = default;
			void Add(); // Adds newline or nothing to the string built.
			void Add(std::string newLine);
			void Add(std::string newLine, unsigned indent, unsigned depth);
			void AddUpper(std::string newLine);
			void AddLower(std::string newLine);
			std::string GetLine(unsigned int position);
			void SetLine(unsigned int position, std::string newLine);
			void Compress(bool ignoreNewLine);
			void Compress(unsigned int beginPostion, unsigned int endPosition, bool ignoreNewLine);
			void CompressFrom(unsigned int beginPostion, bool ignoreNewLine);
			void CompressTill(unsigned int endPostion, bool ignoreNewLine);
			void CombineStringBuilders(std::vector<StringBuilder> stringBuilders);
			std::string GetOutput();
			std::string GetOutputIgnoreNewLine();
			std::string IndentEachLineInString(std::string& stringVariant, unsigned indent, unsigned depth);
	};
}

#endif //DEAMER_STRINGBUILDER_STRINGBUILDER_H