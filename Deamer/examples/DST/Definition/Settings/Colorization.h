#ifndef DST_SETTINGS_DEFINITION_COLORIZATION_H
#define DST_SETTINGS_DEFINITION_COLORIZATION_H

#include "Deamer/Language/Generator/Definition/Property/Standard/Main/Colorization.h"

namespace DST::setting
{
	class Language;

	class Colorization
		: public deamer::language::generator::definition::property::standard::Colorization<
			  ::DST::setting::Language>
	{
	public:
		Colorization(::DST::setting::Language* language)
			: deamer::language::generator::definition::property::standard::Colorization<
				  ::DST::setting::Language>(language)
		{
		}
		~Colorization() override = default;
	};
}

#endif // DST_SETTINGS_DEFINITION_COLORIZATION_H