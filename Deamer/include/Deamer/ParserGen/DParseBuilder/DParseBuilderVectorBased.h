#ifndef DEAMER_PARSERGEN_DPARSEBUILDER_DPARSEBUILDERVECTORBASED_H
#define DEAMER_PARSERGEN_DPARSEBUILDER_DPARSEBUILDERVECTORBASED_H

#include "Deamer/ParserGen/DParseBuilder/DParseBuilder.h"

namespace deamer
{
	class DParseBuilderVectorBased : public DParseBuilder
	{
	public:
		DParseBuilderVectorBased(LanguageDefinition* langDef);
	};
}

#endif //DEAMER_PARSERGEN_DPARSEBUILDER_DPARSEBUILDERVECTORBASED_H