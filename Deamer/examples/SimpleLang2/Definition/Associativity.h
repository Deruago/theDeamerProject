#ifndef SIMPLELANG2_DEFINITION_ASSOCIATIVITY_H
#define SIMPLELANG2_DEFINITION_ASSOCIATIVITY_H

#include "Deamer/Language/Generator/Definition/Property/Standard/Main/Associativity.h"

namespace simplelang
{
	class Language;

	class Associativity : public deamer::language::generator::definition::property::standard::Associativity<simplelang::Language>
	{
	public:
		Associativity(simplelang::Language* language) : deamer::language::generator::definition::property::standard::Associativity<simplelang::Language>(language) {}
		~Associativity() override = default;
	};
}

#endif //SIMPLELANG2_DEFINITION_ASSOCIATIVITY_H