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
 * FileVariable is used to contain logic for variables.
 * You can declare variables using the VariableType and VariableName.
 * You can then use a FileInstructionSection to make instructions such as: b = a + c;
 */

#ifndef DEAMER_FILEBUILDER_FILEVARIABLE_H
#define DEAMER_FILEBUILDER_FILEVARIABLE_H
#include <string>

namespace deamer
{
	class FileVariableType;
	class StringBuilder;
	
	class FileVariable
	{
		private:
			FileVariableType* variableType;
			std::string variableName;
			bool _is_member;

			void AddOutputTypePath(StringBuilder* stringBuilder) const;
			void AddVariableName(StringBuilder* stringBuilder) const;
		protected:
		public:
			FileVariable(FileVariableType* varType, std::string varName, bool isMember);
			virtual ~FileVariable() = default;
			std::string GetOutput() const; // Returns full path. Thus including namespaces and classes. e.g int a, namespace_a::class_b c
			std::string GetVariableName() const; // Returns only the variable name
	};
}

#endif //DEAMER_FILEBUILDER_FILEVARIABLE_H