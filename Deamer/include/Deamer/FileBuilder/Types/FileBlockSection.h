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

#ifndef DEAMER_FILEBUILDER_TYPES_FILEBLOCKSECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEBLOCKSECTION_H
#include "Deamer/FileBuilder/FileSection.h"

namespace deamer
{
	class FileInstructionSection;

	class FileBlockSection : public FileSection
	{
		private:
		protected:
		public:
			FileBlockSection(std::vector<FileInstructionSection*> instruction);
			FileBlockSection() = default;
			~FileBlockSection() = default;
			std::string GetOutput() override;
			void AddInstruction(FileInstructionSection* instruction);
			void AddInstruction(FileInstructionSection* instruction, unsigned int position);
			void RemoveInstruction(FileInstructionSection* instruction);
			void RemoveInstruction(FileInstructionSection* instruction, unsigned int position);
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEBLOCKSECTION_H