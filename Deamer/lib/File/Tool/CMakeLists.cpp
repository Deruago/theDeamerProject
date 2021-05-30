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
