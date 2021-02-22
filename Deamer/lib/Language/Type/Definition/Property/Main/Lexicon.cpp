#include "Deamer/Language/Type/Definition/Property/Main/Lexicon.h"

deamer::language::type::definition::property::main::Lexicon::Lexicon(
	std::vector<object::main::Terminal*> terminals_)
	:	Definition(Type::Lexicon),
		Terminals(std::move(terminals_))
{
}
