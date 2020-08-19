/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstNodeSectionFormatter.h"
#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstFormatter/AstFileFormatterFactory.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstFileType.h"
#include <memory>


deamer::AstVisitorBuilder::AstNodeSectionFormatter::AstNodeSectionFormatter(const std::string& language_name) : AstNodeFormatter(language_name)
{
}

void deamer::AstVisitorBuilder::AstNodeSectionFormatter::MakeAstNode(Token* token, AstFileType ast_file_type)
{
	const std::unique_ptr<AstFileFormatter> formatter = AstFileFormatterFactory().MakeAstFileFormatter(token, language_name_, ast_file_type);
	output += formatter->MakeAstFile();
}