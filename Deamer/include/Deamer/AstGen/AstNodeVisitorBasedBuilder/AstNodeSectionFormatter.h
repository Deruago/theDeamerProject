/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTNODEFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTNODEFORMATTER_H

#include "Deamer/AstGen/AstNodeFormatter.h"
#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstBuilderVisitorBased.h"
#include <string>

namespace deamer
{
	enum class AstFileType;
	class AstFileFormatter;

	namespace AstVisitorBuilder {
	class AstNodeSectionFormatter: public AstNodeFormatter
	{
	private:
	protected:
	public:
		std::string output;
		AstNodeSectionFormatter(const std::string& language_name);
		~AstNodeSectionFormatter() = default;

		void MakeAstNode(Token* token, AstFileType ast_file_type);
	};
}}

#endif //DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTNODEFORMATTER_H