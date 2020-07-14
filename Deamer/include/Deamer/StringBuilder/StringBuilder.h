/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
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