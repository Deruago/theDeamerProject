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

#ifndef DEAMER_FILE_TOOL_CMAKELISTS_H
#define DEAMER_FILE_TOOL_CMAKELISTS_H

#include "Deamer/File/Tool/CMakeListsGenerationVariant.h"
#include "Deamer/File/Tool/CMakeListsType.h"
#include "Deamer/File/Tool/File.h"
#include <string>

namespace deamer::file::tool
{
	/*!	\class CMakeLists
	 *
	 *	\brief This class is used to specify CMakeLists files.
	 *
	 *	\details There are two modes: default_ and custom_. default_ is used
	 *	to automatically deduce the content.
	 *	custom_ is used whenever a custom implementation is given.
	 */
	class CMakeLists
	{
	private:
		CMakeListsType type;
		std::string fileData;
		std::string dependencies;
		CMakeListsGenerationVariant CMG_Variant;
		GenerationLevel generationLevel_;

	public:
		CMakeLists();
		CMakeLists(std::string fileData_, std::string dependencies_ = "",
				   CMakeListsGenerationVariant CMG_Variant_ = CMakeListsGenerationVariant::default_,
				   GenerationLevel generationLevel = GenerationLevel::Always_regenerate);

		~CMakeLists() = default;

	public:
		void SetCMakeLists(const std::string& text);

		void Clear();

	public:
		bool IsDefault() const;

		File GetCMakeLists() const;

		bool IsUserMaintained() const;
	};
}

#endif // DEAMER_FILE_TOOL_CMAKELISTS_H
