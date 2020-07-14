/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
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