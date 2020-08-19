/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstVisitor/AstVisitorSection.h"
#include "Deamer/Types/Generator.h"

deamer::AstVisitorBuilder::AstVisitorSection::AstVisitorSection(const std::string& language_name)
{
	ast_printer_visitor_formatter_ = AstPrinterVisitorFormatter(language_name);
	ast_default_visitor_formatter_ = AstDefaultVisitorFormatter(language_name);
}

void deamer::AstVisitorBuilder::AstVisitorSection::CreateAstVisitorSection()
{
	Generator().CreateDirectoryIfNotExist("./AstNodes/AstVisitor");

	ast_printer_visitor_formatter_.CreateVisitor();
	ast_default_visitor_formatter_.CreateVisitor();
}

void deamer::AstVisitorBuilder::AstVisitorSection::AddToken(Token& token)
{
	ast_printer_visitor_formatter_.AddToken(token);
	ast_default_visitor_formatter_.AddToken(token);
}

void deamer::AstVisitorBuilder::AstVisitorSection::FinishAstVisitorSection()
{
	ast_printer_visitor_formatter_.FinishVisitor();
	ast_default_visitor_formatter_.FinishVisitor();
}
