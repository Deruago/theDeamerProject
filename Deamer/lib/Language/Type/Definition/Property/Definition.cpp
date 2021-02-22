#include "Deamer/Language/Type/Definition/Property/Definition.h"

deamer::language::type::definition::property::Definition::Definition(const property::Type type_)
	: Type(type_)
{	
}

deamer::language::type::definition::property::Type deamer::language::type::definition::property::Definition::
GetType() const noexcept
{
	return Type;
}
