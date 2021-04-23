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

#include "Deamer/File/Tool/File.h"
#include "Deamer/File/Tool/Data.h"

deamer::file::tool::File::File(const std::string& filename_, const std::string& extension_,
							   const Data& data, const GenerationLevel level_)
	: filename(filename_),
	  extension(extension_),
	  fileContent(data.Generate()),
	  level(level_)
{
}

deamer::file::tool::File::File(const std::string& filename_, const std::string& extension_,
							   const std::string& data, const GenerationLevel level_)
	: filename(filename_),
	  extension(extension_),
	  fileContent(data),
	  level(level_)
{
}

deamer::file::tool::GenerationLevel deamer::file::tool::File::GetGenerationLevel() const
{
	return level;
}

void deamer::file::tool::File::SetGenerationLevel(GenerationLevel newLevel)
{
	level = newLevel;
}

std::string deamer::file::tool::File::GetFilename() const
{
	return filename;
}

std::string deamer::file::tool::File::GetExtension() const
{
	return extension;
}

std::string deamer::file::tool::File::FileContent() const
{
	return fileContent;
}

std::string deamer::file::tool::File::GetCompleteFileName() const
{
	return GetFilename() + '.' + GetExtension();
}

void deamer::file::tool::File::SetFileContent(const Data& data)
{
	SetFileContent(data.Generate());
}

void deamer::file::tool::File::SetFileContent(const std::string& data)
{
	fileContent = data;
}

deamer::file::tool::File& deamer::file::tool::File::operator+=(const std::string& cs)
{
	fileContent += cs;

	return *this;
}
