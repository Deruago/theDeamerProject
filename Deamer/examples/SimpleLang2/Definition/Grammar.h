#ifndef SIMPLELANG2_DEFINITION_GRAMMAR_H
#define SIMPLELANG2_DEFINITION_GRAMMAR_H

#include "Deamer/Language/Generator/Definition/Property/User/Main/Grammar.h"

namespace simplelang
{
	class Language;

	class Grammar : public deamer::language::generator::definition::property::user::Grammar<simplelang::Language>
	{
	public:
		Grammar(simplelang::Language* language) : deamer::language::generator::definition::property::user::Grammar<simplelang::Language>(language) {}
		~Grammar() override = default;
	};
}

#endif //SIMPLELANG2_DEFINITION_GRAMMAR_H