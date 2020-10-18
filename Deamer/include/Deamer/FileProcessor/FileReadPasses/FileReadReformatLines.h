/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -October 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREFORMATLINES_H
#define DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREFORMATLINES_H

#include "Deamer/FileProcessor/FileReadPasses/FileReadMidPass.h"
#include <fstream>
#include <vector>

namespace deamer
{
	class FileReadReformatLines : FileReadMidPass
	{
	private:
		void AddCharacterToLine(std::string& line, char newCharacter) const;
		void ResetLineInformation(std::string& line, bool& newLineDetected) const;
	public:
		FileReadReformatLines() = default;

		std::vector<std::string> ProcessLines(std::vector<std::string>& lines) const override;
	};
}

#endif //DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADREFORMATLINES_H