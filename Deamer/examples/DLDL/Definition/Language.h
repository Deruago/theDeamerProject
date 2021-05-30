#ifndef DLDL_DEFINITION_LANGUAGE_H
#define DLDL_DEFINITION_LANGUAGE_H

#include "Deamer/Language/Generator/Definition/Language.h"
#include "Generation.h"
#include "Identity.h"

namespace DLDL
{
	class Language : public ::deamer::language::generator::definition::Language<
						 ::DLDL::Language, ::DLDL::Identity, ::DLDL::Generation>,
					 public ::DLDL::Identity,
					 public ::DLDL::Generation
	{
	public:
		Language() : ::DLDL::Identity(this), ::DLDL::Generation(this)
		{
		}
		~Language() override = default;
	};
}

#endif // DLDL_DEFINITION_LANGUAGE_H
