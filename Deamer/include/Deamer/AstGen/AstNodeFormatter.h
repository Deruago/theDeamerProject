/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEFORMATTER_H

namespace deamer
{
	enum class AstFileType;
	class AstFileFormatter;

	class AstNodeFormatter
	{
	private:
	protected:
	public:
		AstNodeFormatter() = default;
		~AstNodeFormatter() = default;

		void MakeAstNode(AstFileType ast_file_type);
		void MakeAstTree(AstFileType ast_file_type);
	};
}

#endif //DEAMER_ASTGEN_ASTNODEFORMATTER_H