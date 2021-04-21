#ifndef DST_SETTING_DEFINITION_IDENTITY_H
#define DST_SETTING_DEFINITION_IDENTITY_H

#include "Deamer/Language/Generator/Definition/Property/User/Special/Identity.h"

namespace DST::setting
{
	class Language;

	class Identity : public deamer::language::generator::definition::property::user::Identity<
						 DST::setting::Language>
	{
	private:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Name> name;

	public:
		Identity(DST::setting::Language* language)
			: deamer::language::generator::definition::property::user::Identity<
				  DST::setting::Language>(language)
		{
			name.Set(deamer::language::type::definition::object::main::Name("DST_Setting"));
			AddObject(name);
		}
		~Identity() override = default;
	};
}

#endif // DST_SETTING_DEFINITION_IDENTITY_H
