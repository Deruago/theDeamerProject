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

#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstVisitor/AstPrinterVisitorFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/TypeAnalyzer.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/Datastructures/TokenAppearance.h"

deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::AstPrinterVisitorFormatter(const std::string& language_name)
{
	language_name_ = language_name;
}


void deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::CreateVisitor()
{
	header_file_ =	"#ifndef ASTNODES_ASTVISITOR_ASTPRINTER_H\n"
					"\n"
					"/* This is an system generated AstPrinter. We recommend not changing code in this file\n"
					"   If you have improvements, make an pull request.\n"
	                "   If you have suggestions, make an issue or contact a developer or maintainer.\n"
					"*/\n\n"
					"#define ASTNODES_ASTVISITOR_ASTPRINTER_H\n"
					"\n"
					"#include <Deamer/AstGen/AstVisitor.h>\n"
					"\n"
					"namespace " + language_name_ + "\n"
					"{\n";

	header_file_class_definition_ = "    class " + language_name_ + "_AstPrinter : public deamer::AstVisitor\n"
									"    {\n"
									"    private:\n"
									"        unsigned depth = 0;\n"
									"        unsigned indent_size = 4;\n"
									"        std::string MakeIndentation();\n"
									"        std::string MakeIndent();\n"
									"    protected:\n"
									"    public:\n"
									"        " + language_name_ + "_AstPrinter() = default;\n"
									"        void Dispatch(deamer::AstNode& ast_node) override;\n"
									"\n";

	source_file_ =	"#include \"./" + language_name_ + "_AstPrinter.h\"\n"
					"#include \"AstEnum.h\"\n"
					"#include \"AstNodes.h\"\n"
					"#include <iostream>\n"
					"\n";

	source_file_dispatch_ = "void " + language_name_ + "::" + language_name_ + "_AstPrinter::Dispatch(deamer::AstNode& ast_node)\n"
							"{\n"
							"    switch(ast_node.GetAstId())\n"
							"    {\n";
}

void deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::AddToken(Token& token)
{
	source_file_dispatch_ += "    case " + language_name_ + "::AstEnum_t::" + token.TokenName + ":\n"
		"        Visit(static_cast<" + CreateAstNodeClassName(token) + "&>(ast_node));\n"
		"        break;\n";
	source_file_visit_functions += MakeAdditionToSourceFile(token) + "\n";
}

std::string deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::MakeAdditionToSourceFile(Token& token)
{
	if (token.TokenType.has_flag(TokenType_t::start))
		header_file_class_forward_declarations_ += "    class AstTree_" + token.TokenName + ";\n";
	else
		header_file_class_forward_declarations_ += "    class AstNode_" + token.TokenName + ";\n";
		
	header_file_visit_prototypes_ += "        void " + visit_function_prototype(token) + ";\n";

	std::string cases;
	cases += "void " + language_name_ + "::" + language_name_ + "_AstPrinter::" + visit_function_prototype(token) + "\n";
	cases += "{\n";
	cases += PrintAstNode(token);
	if (!token.TokenPermission.has_flag(TokenPermission_t::node))
	{
		cases += "\n";
		if (!token.TokenType.has_flag(TokenType_t::vector))
			cases += "    depth++;\n";
		std::vector<TokenAppearance> token_appearances = TypeAnalyzer(static_cast<Type&>(token)).GetVectorOfMinimalAmountOfTokensUsedDefiningThisType();
		for (TokenAppearance token_appearance : token_appearances)
			for (unsigned token_count = 1; token_count <= token_appearance.token_count; token_count++)
			{
				if (token_appearance.token->TokenType.has_flag(TokenType_t::vector))
					cases += MakeVectorVisit(*token_appearance.token, token_count);
				else
					cases += MakePrinterVisit(*token_appearance.token, token_count);
			}

		if (!token.TokenType.has_flag(TokenType_t::vector))
			cases += "    --depth;\n";
	}
	cases += "}\n";
	return cases;
}

std::string deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::MakeStringBuilderFunctions()
{
	return	"std::string " + language_name_ + "::" + language_name_ + "_AstPrinter::MakeIndentation()\n"
			"{\n"
			"    std::string indentation;\n"
			"    for(unsigned i = 0; i < depth; i++)\n"
			"    {\n"
			"        indentation += MakeIndent();\n"
			"    }\n"
			"    return indentation;\n"
			"}\n"
			"\n"
			"std::string " + language_name_ + "::" + language_name_ + "_AstPrinter::MakeIndent()\n"
			"{\n"
			"    std::string indent;\n"
			"    for(unsigned i = 0; i < indent_size; i++)\n"
			"    {\n"
			"        indent += ' ';\n"
			"    }\n"
			"    return indent;\n"
			"}\n";
}

std::string deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::MakePrinterVisit(const Token& token,
                                                                                    unsigned token_count)
{
    return	"    if (ast_node." + token.TokenName + std::to_string(token_count) + "_ != nullptr)\n"
			"    {\n"
			"        ast_node." + token.TokenName + std::to_string(token_count) + "_->Accept(*this);\n"
			"    }\n";
}

std::string deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::MakeVectorVisit(const Token& token,
	unsigned token_count)
{
	return	"    if (ast_node." + token.TokenName + std::to_string(token_count) + "_ != nullptr)\n"
			"    {\n"
			"        for(int i = (*ast_node." + token.TokenName + std::to_string(token_count) + "_).size() - 1; i >= 0; i--)\n"
			"        {\n"
			"            (*ast_node." + token.TokenName + std::to_string(token_count) + "_)[i]->Accept(*this);\n"
			"        }\n"
			"    }\n";
}

std::string deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::PrintAstNode(const Token& token)
{
	if (token.TokenType.has_flag(TokenType_t::vector))
		return "";
	else if (token.TokenPermission.has_flag(TokenPermission_t::node))
		return "    ast_node.PrintNode(depth);\n";
	else
		return "    std::cout << MakeIndentation() << \"" + token.TokenName + "\" << std::endl;\n";
}

void deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::FinishVisitor()
{
	header_file_ += header_file_class_forward_declarations_ + "\n" +
		header_file_class_definition_ + header_file_visit_prototypes_ +
		"    };\n"
		"}\n"
		"#endif //ASTNODES_ASTVISITOR_ASTPRINTER_H\n";
	source_file_dispatch_ += "    }\n"
		"}\n"
		"\n";
	source_file_ += source_file_visit_functions + source_file_dispatch_ + MakeStringBuilderFunctions();

	WriteOutputToFile("./AstNodes/AstVisitor/" + language_name_ + "_AstPrinter.cpp", source_file_);
	WriteOutputToFile("./AstNodes/AstVisitor/" + language_name_ + "_AstPrinter.h", header_file_);
}

std::string deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::visit_function_prototype(Token& token)
{
    return "Visit(" + CreateAstNodeClassName(token) + "& ast_node)";
}

std::string deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::CreateAstNodeClassName(Token& token)
{
    if (token.TokenType.has_flag(TokenType_t::start))
        return "AstTree_" + token.TokenName;
    else
        return "AstNode_" + token.TokenName;
}
