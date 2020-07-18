#ifndef DEAMER_PARSERGEN_BISONBUILDER_BISONBUILDERVECTORBASED_H
#define DEAMER_PARSERGEN_BISONBUILDER_BISONBUILDERVECTORBASED_H

#include "Deamer/ParserGen/BisonBuilder/BisonBuilder.h"

namespace deamer
{
	class BisonBuilderVectorBased : public BisonBuilder
	{
	public:
		BisonBuilderVectorBased(LanguageDefinition* langDef);
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_BISONBUILDERVECTORBASED_H