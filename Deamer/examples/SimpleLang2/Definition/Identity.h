#ifndef SIMPLELANG2_DEFINITION_IDENTITY_H
#define SIMPLELANG2_DEFINITION_IDENTITY_H

#include "Deamer/Language/Generator/Definition/Property/User/Special/Identity.h"

namespace simplelang
{
	class Language;

	class Identity : public deamer::language::generator::definition::property::user::Identity<
						 simplelang::Language>
	{
	private:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Name> name;

	public:
		Identity(simplelang::Language* language)
			: deamer::language::generator::definition::property::user::Identity<
				  simplelang::Language>(language)
		{
			name.Set(deamer::language::type::definition::object::main::Name("SimpleLang"));
			AddObject(name);
		}
		~Identity() override = default;
	};
}

#endif // SIMPLELANG2_DEFINITION_IDENTITY_H
