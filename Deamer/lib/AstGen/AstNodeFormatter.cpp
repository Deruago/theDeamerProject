/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstNodeFormatter.h"
#include "Deamer/AstGen/AstFormatter/AstFileFormatterFactory.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstType.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstFileType.h"
#include <memory>

void deamer::AstNodeFormatter::MakeAstNode(AstFileType ast_file_type)
{
	const std::unique_ptr<AstFileFormatter> formatter = AstFileFormatterFactory().MakeAstFileFormatter(AstType::node, ast_file_type);
	
}

void deamer::AstNodeFormatter::MakeAstTree(AstFileType ast_file_type)
{
	const std::unique_ptr<AstFileFormatter> formatter = AstFileFormatterFactory().MakeAstFileFormatter(AstType::tree, ast_file_type);
}
