#ifndef DLDL_GRAMMAR_DEFINITION_LANGUAGE_H
#define DLDL_GRAMMAR_DEFINITION_LANGUAGE_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Generation.h"
#include "Grammar.h"
#include "Identity.h"
#include "Lexicon.h"

namespace DLDL::grammar
{
	class Language : public ::deamer::language::generator::definition::Language<
						 ::DLDL::grammar::Language, ::DLDL::grammar::Lexicon, ::DLDL::grammar::Grammar,
						 ::DLDL::grammar::Identity, ::DLDL::grammar::Generation>,
					 public ::DLDL::grammar::Lexicon,
					 public ::DLDL::grammar::Grammar,
					 public ::DLDL::grammar::Identity,
					 public ::DLDL::grammar::Generation
	{
	public:
		Language()
			: ::DLDL::grammar::Lexicon(this),
			  ::DLDL::grammar::Grammar(this),
			  ::DLDL::grammar::Identity(this),
			  ::DLDL::grammar::Generation(this)
		{
		}
		~Language() override = default;
	};
}

#endif // DLDL_GRAMMAR_DEFINITION_LANGUAGE_H
