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

#include "Deamer/File/Tool/CMakeLists.h"
#include <utility>

deamer::file::tool::CMakeLists::CMakeLists()
	: type(CMakeListsType::default_),
	  CMG_Variant(CMakeListsGenerationVariant::default_),
	  generationLevel_(GenerationLevel::Always_regenerate)
{
}

deamer::file::tool::CMakeLists::CMakeLists(std::string fileData_, std::string dependencies_,
										   CMakeListsGenerationVariant CMG_Variant_,
										   GenerationLevel generationLevel)
	: type(CMakeListsType::custom_),
	  fileData(std::move(fileData_)),
	  dependencies(std::move(dependencies_)),
	  CMG_Variant(CMG_Variant_),
	  generationLevel_(generationLevel)
{
}

void deamer::file::tool::CMakeLists::SetCMakeLists(const std::string& text)
{
	type = CMakeListsType::custom_;
	fileData = text;
}

void deamer::file::tool::CMakeLists::Clear()
{
	type = CMakeListsType::default_;
	fileData.clear();
}

bool deamer::file::tool::CMakeLists::IsDefault() const
{
	return type == CMakeListsType::default_;
}

deamer::file::tool::File deamer::file::tool::CMakeLists::GetCMakeLists() const
{
	switch (CMG_Variant)
	{
	case CMakeListsGenerationVariant::user_excluded:
		return File("deamer", "cmake", fileData + dependencies, generationLevel_);
	case CMakeListsGenerationVariant::default_:
		return File("CMakeLists", "txt", fileData + dependencies, generationLevel_);
	default:
		return File("CMakeLists", "txt", fileData + dependencies, generationLevel_);
	}
}

bool deamer::file::tool::CMakeLists::IsUserMaintained() const
{
	return CMG_Variant == CMakeListsGenerationVariant::user_maintained;
}
