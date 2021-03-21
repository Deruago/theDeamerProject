#ifndef SIMPLELANG2_DEFINITION_LANGUAGE_H
#define SIMPLELANG2_DEFINITION_LANGUAGE_H

#include "Associativity.h"
#include "Deamer/Language/Generator/Definition/Language.h"
#include "Generation.h"
#include "Grammar.h"
#include "Identity.h"
#include "Lexicon.h"
#include "Precedence.h"

namespace simplelang
{
	class Language : public deamer::language::generator::definition::Language<
						 simplelang::Language, simplelang::Identity, simplelang::Generation,
						 simplelang::Lexicon, simplelang::Grammar, simplelang::Precedence,
						 simplelang::Associativity>,
					 public simplelang::Lexicon,
					 public simplelang::Grammar,
					 public simplelang::Precedence,
					 public simplelang::Associativity,
					 public simplelang::Identity,
					 public simplelang::Generation
	{
	public:
		Language()
			: simplelang::Lexicon(this),
			  simplelang::Grammar(this),
			  simplelang::Precedence(this),
			  simplelang::Associativity(this),
			  simplelang::Identity(this),
			  simplelang::Generation(this)
		{
		}
		~Language() override = default;
	};
}

#endif // SIMPLELANG2_DEFINITION_LANGUAGE_H
