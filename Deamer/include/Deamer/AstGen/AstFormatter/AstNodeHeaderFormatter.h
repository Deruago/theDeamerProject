/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTFORMATTER_ASTNODEHEADERFORMATTER_H
#define DEAMER_ASTGEN_ASTFORMATTER_ASTNODEHEADERFORMATTER_H
#include "Deamer/AstGen/AstFormatter/AstFileFormatter.h"

namespace deamer
{
	class AstNodeHeaderFormatter : AstFileFormatter
	{
	private:
	protected:
	public:
		AstNodeHeaderFormatter() = default;
		~AstNodeHeaderFormatter() = default;
	};
}

#endif //DEAMER_ASTGEN_ASTFORMATTER_ASTNODEHEADERFORMATTER_H