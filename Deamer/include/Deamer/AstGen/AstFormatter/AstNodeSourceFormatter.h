/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#ifndef DEAMER_ASTGEN_ASTFORMATTER_ASTNODESOURCEFORMATTER_H
#define DEAMER_ASTGEN_ASTFORMATTER_ASTNODESOURCEFORMATTER_H
#include "Deamer/AstGen/AstFormatter/AstFileFormatter.h"

namespace deamer
{
	class AstNodeSourceFormatter : AstFileFormatter
	{
	private:
	protected:
	public:
		AstNodeSourceFormatter() = default;
		~AstNodeSourceFormatter() = default;
	};
}

#endif //DEAMER_ASTGEN_ASTFORMATTER_ASTNODESOURCEFORMATTER_H