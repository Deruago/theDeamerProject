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

#include "Deamer/Type/File/TemporaryFile.h"
#include <array>
#include <charconv>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <sstream>

// Utilized to avoid multiple threads to create the same temporary file
static std::mutex mutex;

static std::size_t temporaryFileCount = 1;

deamer::type::TemporaryFile::TemporaryFile()
{
	std::lock_guard<std::mutex> lockGuard(mutex);

	bool validTemporaryFile = false;
	while (!validTemporaryFile) // As long as there is no valid temporary file, search for one
	{
		// GenerateTemporaryFileName creates a new potential filename.
		// This is done until a valid filename is found
		auto temporaryName = GenerateTemporaryFileName();
		if (std::filesystem::exists(temporaryName))
		{
			continue;
		}
		else
		{
			std::ofstream outfile(temporaryName);
			temporaryFileName = temporaryName;
			validTemporaryFile = true;
		}
	}
}

deamer::type::TemporaryFile::~TemporaryFile()
{
	std::lock_guard<std::mutex> lockGuard(mutex);

	std::error_code existsErrorCode;
	if (std::filesystem::exists(temporaryFileName, existsErrorCode))
	{
		std::error_code removeErrorCode;
		std::filesystem::remove(temporaryFileName, removeErrorCode);
	}
	else
	{
		// It is already deleted
	}
}

deamer::type::TemporaryFile& deamer::type::TemporaryFile::operator=(const std::string& rhs)
{
	Fill(rhs);

	return *this;
}

deamer::type::TemporaryFile& deamer::type::TemporaryFile::operator+=(const std::string& rhs)
{
	Append(rhs);

	return *this;
}

void deamer::type::TemporaryFile::Fill(const std::string& text)
{
	std::ofstream file;
	file.open(GetRelativePath());

	file << text;
}

void deamer::type::TemporaryFile::Append(const std::string& text)
{
	std::ofstream file;
	file.open(GetRelativePath(), std::ios::app);

	file << text;
}

std::string deamer::type::TemporaryFile::GetContent()
{
	std::ifstream file;
	file.open(GetRelativePath());

	std::ostringstream fileContent;
	fileContent << file.rdbuf();

	return fileContent.str();
}

std::string deamer::type::TemporaryFile::GetRelativePath()
{
	return "./" + temporaryFileName;
}

std::string deamer::type::TemporaryFile::GetFileName()
{
	return temporaryFileName;
}

std::string deamer::type::TemporaryFile::GenerateTemporaryFileName()
{
	// This allows for 36 ^ 13 combinations, this is more combination than 64 bit integer limit
	std::array<char, 13> str{};
	auto [ptr, ec] = std::to_chars(str.data(), str.data() + str.size(), temporaryFileCount++, 36);

	const std::size_t nameLength = ptr - str.data();

	return "dtemp_" + std::string(str.data(), nameLength);
}
