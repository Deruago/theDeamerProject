#ifndef DST_SETTING_DEFINITION_LANGUAGE_H
#define DST_SETTING_DEFINITION_LANGUAGE_H

#include "Colorization.h"
#include "Deamer/Language/Generator/Definition/Language.h"
#include "Generation.h"
#include "Grammar.h"
#include "Identity.h"
#include "Lexicon.h"

namespace DST::setting
{
	class Language
		: public ::deamer::language::generator::definition::Language<
			  ::DST::setting::Language, ::DST::setting::Lexicon, ::DST::setting::Grammar,
			  ::DST::setting::Identity, ::DST::setting::Generation, ::DST::setting::Colorization>,
		  public ::DST::setting::Lexicon,
		  public ::DST::setting::Grammar,
		  public ::DST::setting::Identity,
		  public ::DST::setting::Generation,
		  public ::DST::setting::Colorization
	{
	public:
		Language()
			: ::DST::setting::Lexicon(this),
			  ::DST::setting::Grammar(this),
			  ::DST::setting::Identity(this),
			  ::DST::setting::Generation(this),
			  ::DST::setting::Colorization(this)
		{
		}
		~Language() override = default;
	};
}

#endif // DST_SETTING_DEFINITION_LANGUAGE_H
