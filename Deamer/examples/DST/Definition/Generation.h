#ifndef DST_DEFINITION_GENERATION_H
#define DST_DEFINITION_GENERATION_H

#include "Deamer/Language/Generator/Definition/Property/User/Special/Generation.h"

namespace DST
{
	class Language;

	class Generation
		: public deamer::language::generator::definition::property::user::Generation<DST::Language>
	{
	private:
	public:
		Generation(DST::Language* language)
			: deamer::language::generator::definition::property::user::Generation<DST::Language>(
				  language)
		{
		}
		~Generation() override = default;
	};
}

#endif // DST_DEFINITION_GENERATION_H
