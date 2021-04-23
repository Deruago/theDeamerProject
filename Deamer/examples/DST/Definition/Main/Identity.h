#ifndef DST_MAIN_DEFINITION_IDENTITY_H
#define DST_MAIN_DEFINITION_IDENTITY_H

#include "Deamer/Language/Generator/Definition/Property/User/Special/Identity.h"

namespace DST::main
{
	class Language;

	class Identity : public deamer::language::generator::definition::property::user::Identity<
						 DST::main::Language>
	{
	private:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Name> name;

	public:
		Identity(DST::main::Language* language)
			: deamer::language::generator::definition::property::user::Identity<
				  DST::main::Language>(language)
		{
			name.Set(deamer::language::type::definition::object::main::Name("DST_Main"));
			AddObject(name);
		}
		~Identity() override = default;
	};
}

#endif // DST_MAIN_DEFINITION_IDENTITY_H
