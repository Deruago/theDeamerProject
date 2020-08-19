/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#include "Deamer/AstGen/AstNodeFormatter.h"
#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstFormatter/AstFileFormatterFactory.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstFileType.h"
#include <memory>


deamer::AstNodeFormatter::AstNodeFormatter(std::string language_name)
{
	language_name_ = language_name;
}

void deamer::AstNodeFormatter::MakeAstNode(Token* token, AstFileType ast_file_type)
{
	const std::unique_ptr<AstFileFormatter> formatter = AstFileFormatterFactory().MakeAstFileFormatter(token, language_name_, ast_file_type);
	output += formatter->MakeAstFile();
}

void deamer::AstNodeFormatter::MakeAstTree(Token* token, AstFileType ast_file_type)
{
	const std::unique_ptr<AstFileFormatter> formatter = AstFileFormatterFactory().MakeAstFileFormatter(token, language_name_, ast_file_type);
	output += formatter->MakeAstFile();
}
