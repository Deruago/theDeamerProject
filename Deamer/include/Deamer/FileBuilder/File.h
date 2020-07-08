/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_FILEBUILDER_FILE_H
#define DEAMER_FILEBUILDER_FILE_H
#include <string>

namespace deamer
{
	class File
	{
		private:
		protected:
			std::string FileName;
			std::string FileExtension;
		public:
			File(std::string fileName, std::string fileExtension);
			~File() = default;
			std::string GetFileName() const;
			std::string GetFileExtension() const;
	};
}

#endif //DEAMER_FILEBUILDER_FILE_H