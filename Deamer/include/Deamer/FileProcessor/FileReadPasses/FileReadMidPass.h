/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
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