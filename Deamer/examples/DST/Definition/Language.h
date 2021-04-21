#ifndef DST_DEFINITION_LANGUAGE_H
#define DST_DEFINITION_LANGUAGE_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Generation.h"
#include "Identity.h"

namespace DST
{
	class Language : public ::deamer::language::generator::definition::Language<
						 ::DST::Language, ::DST::Identity, ::DST::Generation>,
					 public ::DST::Identity,
					 public ::DST::Generation
	{
	public:
		Language() : ::DST::Identity(this), ::DST::Generation(this)
		{
		}
		~Language() override = default;
	};
}

#endif // DST_DEFINITION_LANGUAGE_H
