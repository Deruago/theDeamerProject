/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -October 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREMOVELINESSTARTINGWITHCHARACTER_H
#define DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREMOVELINESSTARTINGWITHCHARACTER_H

#include "Deamer/FileProcessor/FileReadPasses/FileReadMidPass.h"
#include <fstream>
#include <vector>

namespace deamer
{
	class FileReadRemoveLinesStartingWithCharacter : FileReadMidPass
	{
	private:
		std::string illegal_characters_;
		
		bool DoesLineStartWithIllegalCharacter(const std::string& line) const;
	public:
		FileReadRemoveLinesStartingWithCharacter(const std::string& illegal_characters);

		std::vector<std::string> ProcessLines(std::vector<std::string>& lines) const override;
	};
}

#endif //DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREMOVELINESSTARTINGWITHCHARACTER_H