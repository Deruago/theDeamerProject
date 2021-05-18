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

#include "File.h"
#include <string>
#include <utility>

namespace deamer::file::tool
{
	enum class CMakeLists_type
	{
		default_,
		custom_,
	};

	enum class CMakeLists_Generation_Variant
	{
		// CMakeLists.txt
		default_,

		// deamer.cmake ; this gets included in the default cmakelists.txt
		user_excluded,

		// User mainained
		user_maintained,
	};

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
		CMakeLists_type type = CMakeLists_type::default_;
		std::string fileData;
		std::string dependencies;
		CMakeLists_Generation_Variant CMG_Variant = CMakeLists_Generation_Variant::default_;
		GenerationLevel generationLevel_;

	public:
		CMakeLists() = default;
		CMakeLists(
			std::string fileData_, std::string dependencies_ = "",
			CMakeLists_Generation_Variant CMG_Variant_ = CMakeLists_Generation_Variant::default_,
			GenerationLevel generationLevel = GenerationLevel::Always_regenerate)
			: type(CMakeLists_type::custom_),
			  fileData(std::move(fileData_)),
			  dependencies(std::move(dependencies_)),
			  CMG_Variant(CMG_Variant_),
			  generationLevel_(generationLevel)
		{
		}
		~CMakeLists() = default;

	public:
		void SetCMakeLists(const std::string& text)
		{
			type = CMakeLists_type::custom_;
			fileData = text;
		}

		void Clear()
		{
			type = CMakeLists_type::default_;
			fileData.clear();
		}

	public:
		bool IsDefault() const
		{
			return type == CMakeLists_type::default_;
		}

		File GetCMakeLists() const
		{
			switch (CMG_Variant)
			{
			case CMakeLists_Generation_Variant::user_excluded:
				return File("deamer", "cmake", fileData + dependencies, generationLevel_);
			case CMakeLists_Generation_Variant::default_:
				return File("CMakeLists", "txt", fileData + dependencies, generationLevel_);
			default:
				return File("CMakeLists", "txt", fileData + dependencies, generationLevel_);
			}
		}

		bool IsUserMaintained() const
		{
			return CMG_Variant == CMakeLists_Generation_Variant::user_maintained;
		}
	};
}

#endif // DEAMER_FILE_TOOL_CMAKELISTS_H
