#ifndef DST_MAIN_DEFINITION_LANGUAGE_H
#define DST_MAIN_DEFINITION_LANGUAGE_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Generation.h"
#include "Grammar.h"
#include "Identity.h"
#include "Lexicon.h"

namespace DST::main
{
	class Language : public ::deamer::language::generator::definition::Language<
						 ::DST::main::Language, ::DST::main::Lexicon, ::DST::main::Grammar,
						 ::DST::main::Identity, ::DST::main::Generation>,
					 public ::DST::main::Lexicon,
					 public ::DST::main::Grammar,
					 public ::DST::main::Identity,
					 public ::DST::main::Generation
	{
	public:
		Language()
			: ::DST::main::Lexicon(this),
			  ::DST::main::Grammar(this),
			  ::DST::main::Identity(this),
			  ::DST::main::Generation(this)
		{
		}
		~Language() override = default;
	};
}

#endif // DST_MAIN_DEFINITION_LANGUAGE_H
