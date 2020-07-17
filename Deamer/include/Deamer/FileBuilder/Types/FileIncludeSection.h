/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEBUILDER_TYPES_FILEINCLUDESECTION_H
#define DEAMER_FILEBUILDER_TYPES_FILEINCLUDESECTION_H
#include "Deamer/FileBuilder/FileSection.h"
#include <string>

namespace deamer
{
	class FileIncludeSection : public FileSection
	{
		private:
			std::string output;
		public:
			FileIncludeSection(std::string include, bool isSystem);
			std::string GetOutput() override;
	};
}

#endif //DEAMER_FILEBUILDER_TYPES_FILEINCLUDESECTION_H
