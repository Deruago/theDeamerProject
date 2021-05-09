#ifndef DLDL_DEFINITION_IDENTITY_H
#define DLDL_DEFINITION_IDENTITY_H

#include "Deamer/Language/Generator/Definition/Property/User/Special/Identity.h"

namespace DLDL
{
	class Language;

	class Identity
		: public deamer::language::generator::definition::property::user::Identity<DLDL::Language>
	{
	private:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Name> name;

	public:
		Identity(DLDL::Language* language)
			: deamer::language::generator::definition::property::user::Identity<DLDL::Language>(
				  language)
		{
			name.Set(deamer::language::type::definition::object::main::Name("DLDL"));
			AddObject(name);
		}
		~Identity() override = default;
	};
}

#endif // DLDL_DEFINITION_IDENTITY_H
