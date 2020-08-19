/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTNODEHEADERFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTNODEHEADERFORMATTER_H
#include "Deamer/AstGen/AstFileFormatter.h"

namespace deamer
{
	class AstNodeHeaderFormatter : public AstFileFormatter
	{
	private:
	protected:
	public:
		AstNodeHeaderFormatter(Token* token, std::string language_name);
		~AstNodeHeaderFormatter() = default;
		std::string MakeAstFile() const override;
	};
}

#endif //DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTNODEHEADERFORMATTER_H