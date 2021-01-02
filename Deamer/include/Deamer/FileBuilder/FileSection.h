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

/*
 * FileSection is used to define "Sections".
 * Sections are important. They are used to create files.
 * Now sections are general and only apply for c++. Later there will be options to have language specific sections.
 * But the idea of sections is to make specific logic for specific cases.
 * e.g a class section needs to define functions, and a functionsection needs to define a function.
 */

#ifndef DEAMER_FILEBUILDER_FILESECTION_H
#define DEAMER_FILEBUILDER_FILESECTION_H
#include <vector>
#include <string>

namespace deamer
{
	class Directory;
	class File;
	
	class FileSection
	{
		private:
			File* _File;
			Directory* _Directory;
		protected:
			std::string Output;
			std::string FileLocationRelative;
			std::string FileLocationAbsolute;
			std::vector<FileSection*> FileSections;
			void AddSection(FileSection* newSection); // Used to add sections to a class.
		public:
			FileSection(Directory* directory, File* file);
			FileSection();
			virtual ~FileSection() = default;
			virtual std::string GetOutput();
			Directory* GetDirectory() const;
			File* GetFile() const;
			template<typename T, typename A>
			void delete_members(std::vector<T, A> _list);
	};

	template<typename T, typename A>
	void deamer::FileSection::delete_members(std::vector<T, A> _list)
	{
		for (T member : _list)
		{
			delete member;
		}
	}

}

#endif //DEAMER_FILEBUILDER_FILESECTION_H