/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADPASS_H
#define DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADPASS_H
#include <fstream>
#include <vector>

namespace deamer
{
	class FileReadPass
	{
	public:
		virtual ~FileReadPass() = default;
		virtual std::vector<std::string> ProcessFile(std::ifstream& input_file) const = 0;
	private:
	};
}

#endif //DEAMER_FILEPROCESSOR_FILEREADPASSES_FILEREADPASS_H