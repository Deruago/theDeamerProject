/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEFORMATTER_H
#include <string>

#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstBuilderVisitorBased.h"

namespace deamer
{
	enum class AstFileType;
	class AstFileFormatter;

	class AstNodeFormatter
	{
	private:
	protected:
		std::string language_name_;
	public:
		std::string output;
		AstNodeFormatter() = default;
		AstNodeFormatter(const std::string& language_name);
		~AstNodeFormatter() = default;

		std::string MakeClassName(const Token* token) const;
	};
}

#endif //DEAMER_ASTGEN_ASTNODEFORMATTER_H