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
 * FileInstructionSection is used for defining instructions.
 * Currently this can be done through strings and FileVariable objects.
 * Currently this will only be constant generated only. And wont be updated when other objects updates unlike most other Types.
 */

#ifndef DEAMER_FILEBUILDER_TYPES_FILEINSTRUCTIONSECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEINSTRUCTIONSECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include <string>

namespace deamer
{
	class FileVariable;

	class FileInstructionSection : public FileSection
	{
		private:
		protected:
		public:
			FileInstructionSection() = default;
			~FileInstructionSection() = default;
			void AddInstruction(std::string instruction);
			void AddAsignment(FileVariable* variable, std::string assignment);
			void AddDeclaration(FileVariable* variable);
			void AddReturnInstruction(std::string instruction);
			std::string GetOutput() override;
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEINSTRUCTIONSECTION_H