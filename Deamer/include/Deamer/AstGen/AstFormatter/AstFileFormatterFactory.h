/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTFORMATTER_ASTFILEFORMATTERFACTORY_H
#define DEAMER_ASTGEN_ASTFORMATTER_ASTFILEFORMATTERFACTORY_H
#include "Deamer/AstGen/AstFormatter/AstFileFormatter.h"

namespace deamer
{
	enum class AstType;
	enum class AstFileType;

	class AstFileFormatterFactory
	{
	private:
	protected:
	public:
		AstFileFormatterFactory() = default;
		~AstFileFormatterFactory() = default;

		const AstFileFormatter MakeAstFileFormatter(AstType ast_type, AstFileType ast_file_type) const;
	};
}

#endif //DEAMER_ASTGEN_ASTFORMATTER_ASTFILEFORMATTERFACTORY_H