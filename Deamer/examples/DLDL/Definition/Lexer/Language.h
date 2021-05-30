#ifndef DLDL_LEXER_DEFINITION_LANGUAGE_H
#define DLDL_LEXER_DEFINITION_LANGUAGE_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Generation.h"
#include "Grammar.h"
#include "Identity.h"
#include "Lexicon.h"

namespace DLDL::lexer
{
	class Language : public ::deamer::language::generator::definition::Language<
						 ::DLDL::lexer::Language, ::DLDL::lexer::Lexicon, ::DLDL::lexer::Grammar,
						 ::DLDL::lexer::Identity, ::DLDL::lexer::Generation>,
					 public ::DLDL::lexer::Lexicon,
					 public ::DLDL::lexer::Grammar,
					 public ::DLDL::lexer::Identity,
					 public ::DLDL::lexer::Generation
	{
	public:
		Language()
			: ::DLDL::lexer::Lexicon(this),
			  ::DLDL::lexer::Grammar(this),
			  ::DLDL::lexer::Identity(this),
			  ::DLDL::lexer::Generation(this)
		{
		}
		~Language() override = default;
	};
}

#endif // DLDL_LEXER_DEFINITION_LANGUAGE_H
