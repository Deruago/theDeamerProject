/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEBUILDER_TYPES_FILEBLOCKSECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEBLOCKSECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include "Deamer/FileBuilder/Types/FileInstructionSection.h"

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