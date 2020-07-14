#ifndef DEAMER_FILEBUILDER_CPPFILEBUILDER_H
#define DEAMER_FILEBUILDER_CPPFILEBUILDER_H
#include "Deamer/FileBuilder/FileBuilder.h"
#include <string>

namespace deamer
{
	class CPPFileBuilder : FileBuilder
	{
		private:
		protected:
		public:
			CPPFileBuilder(std::string directoryName, std::string fileName);
			~CPPFileBuilder() = default;
			std::string GetOutput() const override;
	};
}

#endif //DEAMER_FILEBUILDER_CPPFILEBUILDER_H