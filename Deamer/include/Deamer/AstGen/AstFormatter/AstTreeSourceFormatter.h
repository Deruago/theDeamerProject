/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTFORMATTER_ASTTREESOURCERFORMATTER_H
#define DEAMER_ASTGEN_ASTFORMATTER_ASTTREESOURCERFORMATTER_H
#include "Deamer/AstGen/AstFormatter/AstFileFormatter.h"

namespace deamer
{
	class AstTreeSourceFormatter : public AstFileFormatter
	{
	private:
	protected:
	public:
		AstTreeSourceFormatter() = default;
		~AstTreeSourceFormatter() = default;
	};
}

#endif //DEAMER_ASTGEN_ASTFORMATTER_ASTTREESOURCERFORMATTER_H