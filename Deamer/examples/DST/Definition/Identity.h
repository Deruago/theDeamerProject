#ifndef DST_DEFINITION_IDENTITY_H
#define DST_DEFINITION_IDENTITY_H

#include "Deamer/Language/Generator/Definition/Property/User/Special/Identity.h"

namespace DST
{
	class Language;

	class Identity
		: public deamer::language::generator::definition::property::user::Identity<DST::Language>
	{
	private:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Name> name;

	public:
		Identity(DST::Language* language)
			: deamer::language::generator::definition::property::user::Identity<DST::Language>(
				  language)
		{
			name.Set(deamer::language::type::definition::object::main::Name("DST"));
			AddObject(name);
		}
		~Identity() override = default;
	};
}

#endif // DST_DEFINITION_IDENTITY_H
