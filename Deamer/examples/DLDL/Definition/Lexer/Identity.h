#ifndef DLDL_LEXER_DEFINITION_IDENTITY_H
#define DLDL_LEXER_DEFINITION_IDENTITY_H

#include "Deamer/Language/Generator/Definition/Property/User/Special/Identity.h"

namespace DLDL::lexer
{
	class Language;

	class Identity : public deamer::language::generator::definition::property::user::Identity<
						 DLDL::lexer::Language>
	{
	private:
		deamer::type::SafeReserve<deamer::language::type::definition::object::main::Name> name;

	public:
		Identity(DLDL::lexer::Language* language)
			: deamer::language::generator::definition::property::user::Identity<
				  DLDL::lexer::Language>(language)
		{
			name.Set(deamer::language::type::definition::object::main::Name("DLDL_LEXER"));
			AddObject(name);
		}
		~Identity() override = default;
	};
}

#endif // DLDL_LEXER_DEFINITION_IDENTITY_H
