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

#include "AstNodeInterpreterBasedBuilder/AstBuilder.h"

namespace deamer
{
	enum class AstFileType;
	class AstFileFormatter;

	class AstNodeFormatter
	{
	private:
		std::string language_name_;
	protected:
	public:
		std::string output;
		AstNodeFormatter(std::string language_name);
		~AstNodeFormatter() = default;

		void MakeAstNode(Token* token, AstFileType ast_file_type);
		void MakeAstTree(Token* token, AstFileType ast_file_type);
	};
}

#endif //DEAMER_ASTGEN_ASTNODEFORMATTER_H