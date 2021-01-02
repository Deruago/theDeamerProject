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
 * Is used to contain logic for FileVariableTypes.
 * Types are basically things such as: int, string, char, std::vector<T>, namespace_a::class_b ect
 * This class is abstract and is used as an interface. As types are classes it uses a FileClassSection
 */

#ifndef DEAMER_FILEBUILDER_FILEVARIABLETYPE_H
#define DEAMER_FILEBUILDER_FILEVARIABLETYPE_H
#include <string>

namespace deamer
{
	class FileVariableType
	{
		private:
			FileVariableType* _variableTypeSection;
		protected:
		public:
			FileVariableType(FileVariableType* variableTypeSection);
			FileVariableType();
			virtual ~FileVariableType() = default;
			FileVariableType* GetFileVariableType() const;
			virtual std::string GetOutputType() const = 0; //Outputs Variabletype. e.g deamer::filebuilder::class_a
	};
}

#endif //DEAMER_FILEBUILDER_FILEVARIABLETYPE_H