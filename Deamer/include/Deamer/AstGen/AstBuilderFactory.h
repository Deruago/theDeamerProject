/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTBUILDERFACTORY_H
#define DEAMER_ASTGEN_ASTBUILDERFACTORY_H

#include "Deamer/AstGen/AstBuilder.h"
#include <memory>

namespace deamer
{
	enum class AstBuilderType;

	class AstBuilderFactory
	{
	private:
	protected:
	public:
		AstBuilderFactory() = default;
		~AstBuilderFactory() = default;

		std::unique_ptr<AstBuilder> MakeAstBuilder(AstBuilderType ast_builder_type, const std::string& directory, const std::string& language_name) const;
	};
}

#endif //DEAMER_ASTGEN_ASTBUILDERFACTORY_H