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

#ifndef DEAMER_FILE_TOOL_FILE_H
#define DEAMER_FILE_TOOL_FILE_H
#include <string>

namespace deamer::file::tool
{
	class Data;

	/*!	\enum GenerationLevel
	 *
	 *	\brief Defines the different levels of generation.
	 *
	 *	\details It might be that a file should only be generated if the target in question hasn't
	 *been generated already. In such cases one may change the generation level to suite the
	 *generation style.
	 */
	enum class GenerationLevel
	{
		unknown,

		Always_regenerate,
		Dont_generate_if_file_already_exists,
	};

	class File
	{
	private:
		std::string filename;
		std::string extension;
		std::string fileContent;
		GenerationLevel level = GenerationLevel::Always_regenerate;

	public:
		File(const std::string& filename_, const std::string& extension_, const Data& data,
			 const GenerationLevel level_ = GenerationLevel::Always_regenerate);
		File(const std::string& filename_, const std::string& extension_,
			 const std::string& data = "",
			 const GenerationLevel level_ = GenerationLevel::Always_regenerate);

		virtual ~File() = default;

	public:
		GenerationLevel GetGenerationLevel() const;
		std::string GetFilename() const;
		std::string GetExtension() const;
		std::string FileContent() const;
		std::string GetCompleteFileName() const;

		void SetGenerationLevel(GenerationLevel newLevel);
		void SetFileContent(const Data& data);
		void SetFileContent(const std::string& data);

		deamer::file::tool::File& operator+=(const std::string& cs);
	};
}

#endif // DEAMER_FILE_TOOL_FILE_H
