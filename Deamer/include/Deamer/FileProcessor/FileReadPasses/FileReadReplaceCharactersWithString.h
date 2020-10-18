/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -October 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREPLACECHARACTERSWITHSTRING_H
#define DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREPLACECHARACTERSWITHSTRING_H

#include "Deamer/FileProcessor/FileReadPasses/FileReadMidPass.h"
#include <fstream>
#include <vector>

namespace deamer
{
	class FileReadReplaceCharactersWithString : FileReadMidPass
	{
	private:
		std::string characters_to_replace_;
		std::string inserted_string_;

		bool shouldCharacterBeReplaced(const char character) const;
		std::string createUpdatedLine(const std::string& oldLine) const;
	public:
		FileReadReplaceCharactersWithString(const std::string& characters_to_replace, const std::string& inserted_string);

		std::vector<std::string> ProcessLines(std::vector<std::string>& lines) const override;
	};
}

#endif //DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREPLACECHARACTERSWITHSTRING_H