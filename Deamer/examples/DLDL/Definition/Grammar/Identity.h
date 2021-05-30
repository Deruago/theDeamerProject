#ifndef DLDL_GRAMMAR_DEFINITION_IDENTITY_H
#define DLDL_GRAMMAR_DEFINITION_IDENTITY_H

#include "Deamer/Language/Generator/Definition/Property/User/Special/Identity.h"

namespace DLDL::grammar
{
	class Language;

	class Identity : public deamer::language::generator::definition::property::user::Identity<
						 DLDL::grammar::Language>
	{
	private:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Name> name;

	public:
		Identity(DLDL::grammar::Language* language)
			: deamer::language::generator::definition::property::user::Identity<
				  DLDL::grammar::Language>(language)
		{
			name.Set(deamer::language::type::definition::object::main::Name("DLDL_GRAMMAR"));
			AddObject(name);
		}
		~Identity() override = default;
	};
}

#endif // DLDL_GRAMMAR_DEFINITION_IDENTITY_H
