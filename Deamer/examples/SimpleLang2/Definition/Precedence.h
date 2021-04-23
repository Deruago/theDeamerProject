#ifndef SIMPLELANG2_DEFINITION_PRECEDENCE_H
#define SIMPLELANG2_DEFINITION_PRECEDENCE_H

#include "Deamer/Language/Generator/Definition/Property/Standard/Main/Precedence.h"

namespace simplelang
{
	class Language;

	class Precedence : public deamer::language::generator::definition::property::standard::Precedence<simplelang::Language>
	{
	public:
		Precedence(simplelang::Language* language) : deamer::language::generator::definition::property::standard::Precedence<simplelang::Language>(language) {}
		~Precedence() override = default;
	};
}

#endif //SIMPLELANG2_DEFINITION_PRECEDENCE_H