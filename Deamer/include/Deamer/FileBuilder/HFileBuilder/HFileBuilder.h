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

#ifndef DEAMER_FILEBUILDER_HFILEBUILDER_H
#define DEAMER_FILEBUILDER_HFILEBUILDER_H
#include "Deamer/FileBuilder/FileBuilder.h"
#include <vector>
#include <string>

namespace deamer
{
	class FileHeaderSection;
	
	class HFileBuilder : FileBuilder
	{
		private:
		protected:
			FileHeaderSection* headerSection;
		public:
			HFileBuilder(Directory* directory, File* file);
			HFileBuilder(std::vector<std::string> directories, std::string fileName, std::string extension);
			void CreateHeaderGuardSection(const Directory* directory, const File* file) const;
			~HFileBuilder() = default;
			std::string GetOutput() const override;
			FileHeaderSection* GetHeaderSection() const;
			void AddInclude(std::string _path) const;
	};
}

#endif //DEAMER_FILEBUILDER_HFILEBUILDER_H