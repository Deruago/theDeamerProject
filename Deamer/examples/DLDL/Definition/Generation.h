#ifndef DLDL_DEFINITION_GENERATION_H
#define DLDL_DEFINITION_GENERATION_H

#include "Deamer/Language/Generator/Definition/Property/User/Special/Generation.h"

namespace DLDL
{
	class Language;

	class Generation
		: public deamer::language::generator::definition::property::user::Generation<DLDL::Language>
	{
	private:
	public:
		Generation(DLDL::Language* language)
			: deamer::language::generator::definition::property::user::Generation<DLDL::Language>(
				  language)
		{
		}
		~Generation() override = default;
	};
}

#endif // DLDL_DEFINITION_GENERATION_H
