#ifndef DEAMER_FILEBUILDER_HFILEBUILDER_H
#define DEAMER_FILEBUILDER_HFILEBUILDER_H
#include "Deamer/FileBuilder/FileBuilder.h"
#include "Deamer/FileBuilder/Types/FileHeaderSection.h"

namespace deamer
{
	class HFileBuilder : FileBuilder
	{
		private:
		protected:
			FileHeaderSection* headerSection;
		public:
			HFileBuilder(Directory* directory, File* file);
			HFileBuilder(std::vector<std::string> directories, std::string fileName, std::string extension);
			void CreateHeaderGuardSection(const Directory* directory, const File* file) const;
			~HFileBuilder() = default;
			std::string GetOutput() const override;
			FileHeaderSection* GetHeaderSection() const;
	};
}

#endif //DEAMER_FILEBUILDER_HFILEBUILDER_H