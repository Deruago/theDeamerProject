#include "Deamer/Language/Reference/LanguageReferenceRequest.h"

deamer::language::reference::LanguageReferenceRequest::LanguageReferenceRequest(
	const type::definition::property::Type type_, const RequirementLevel level) noexcept
	:	Type(type_),
	    Level(level)
{
}

deamer::language::type::definition::property::Type deamer::language::reference::LanguageReferenceRequest::
GetPropertyType() const noexcept
{
	return Type;
}

deamer::language::reference::RequirementLevel deamer::language::reference::LanguageReferenceRequest::
GetRequirementLevel() const noexcept
{
	return Level;
}
