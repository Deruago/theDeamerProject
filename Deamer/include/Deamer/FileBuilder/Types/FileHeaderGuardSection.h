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

#ifndef DEAMER_FILEBUILDER_TYPES_FILEHEADERGUARDSECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEHEADERGUARDSECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include <string>

namespace deamer
{
	class Directory;
	class File;
	class StringBuilder;
	
	class FileHeaderGuardSection : public FileSection
	{
		private:
		protected:
			std::string HeaderGuardBegin;
			std::string HeaderGuardEnd;
			void AddFileToHeaderGuardMacro(StringBuilder* string, const File* file);
			void AddDirectoryToHeaderGuardMacro(StringBuilder* string, const Directory* directory);
			std::string GetHeaderGuardMacro(const Directory* directory, const File* file);
			std::string GetHeaderGuardMacroDefinition(const Directory* directory, const File* file);
			std::string GetHeaderGuardMacroIfNotDefinedCheck(const Directory* directory, const File* file);
			void SetHeaderGuardBegin(const Directory* directory, const File* file);
			void SetHeaderGuardEnd(const Directory* directory, const File* file);
		public:
			FileHeaderGuardSection(Directory* directory, File* file);
			~FileHeaderGuardSection() = default;
			std::string GetHeaderGuardBegin() const;
			std::string GetHeaderGuardEnd() const;
			std::string GetOutput() override;
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEHEADERGUARDSECTION_H