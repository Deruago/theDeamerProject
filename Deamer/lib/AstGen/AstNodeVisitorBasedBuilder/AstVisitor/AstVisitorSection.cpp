/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
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
