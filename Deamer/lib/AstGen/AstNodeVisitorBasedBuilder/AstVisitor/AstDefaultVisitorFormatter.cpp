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

#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstVisitor/AstDefaultVisitorFormatter.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/TypeAnalyzer.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/Datastructures/TokenAppearance.h"

deamer::AstVisitorBuilder::AstDefaultVisitorFormatter::AstDefaultVisitorFormatter(const std::string& language_name)
{
	language_name_ = language_name;
}

void deamer::AstVisitorBuilder::AstDefaultVisitorFormatter::CreateVisitor()
{
	header_file_ =	"#ifndef ASTNODES_ASTVISITOR_ASTVISITOR_H\n"
					"#define ASTNODES_ASTVISITOR_ASTVISITOR_H\n"
					"\n"
					"#include <Deamer/AstGen/AstVisitor.h>\n"
					"\n"
					"namespace " + language_name_ + "\n"
					"{\n";
	
	header_file_class_definition_ = "    class " + language_name_ + "_AstVisitor : public deamer::AstVisitor\n"
									"    {\n"
									"    private:\n"
									"    protected:\n"
									"    public:\n"
									"        " + language_name_ + "_AstVisitor() = default;\n"
									"        void Dispatch(deamer::AstNode& ast_node) override;\n"
									"\n";
	
	source_file_ = "#include \"./" + language_name_ + "_AstVisitor.h\"\n"
				   "#include \"AstEnum.h\"\n"
				   "#include \"AstNodes.h\"\n"
					"\n";
	
	source_file_dispatch_ =	"void " + language_name_ + "::" + language_name_ + "_AstVisitor::Dispatch(deamer::AstNode& ast_node)\n"
							"{\n"
							"    switch(ast_node.GetAstId())\n"
							"    {\n";					
}

void deamer::AstVisitorBuilder::AstDefaultVisitorFormatter::AddToken(Token& token)
{
	source_file_dispatch_ += "    case " + language_name_ + "::AstEnum_t::" + token.TokenName + ":\n"
							"        Visit(static_cast<" + CreateAstNodeClassName(token) + "&>(ast_node));\n"
							"        break;\n";
	source_file_visit_functions += MakeAdditionToSourceFile(token) + "\n";
}

std::string deamer::AstVisitorBuilder::AstDefaultVisitorFormatter::MakeAdditionToSourceFile(Token& token)
{
	if (token.TokenType.has_flag(TokenType_t::start))
		header_file_class_forward_declarations_ += "    class AstTree_" + token.TokenName + ";\n";
	else
		header_file_class_forward_declarations_ += "    class AstNode_" + token.TokenName + ";\n";
	
	header_file_visit_prototypes_ += "        void " + visit_function_prototype(token) + ";\n";
	
	std::string cases;
	cases += "void " + language_name_ + "::" + language_name_ + "_AstVisitor::" + visit_function_prototype(token) + "\n";
	cases += "{\n";
	if (token.TokenPermission.has_flag(TokenPermission_t::node))
	{
		cases += MakeDefaultVisit(token, 1);
	}
	else
	{
		std::vector<TokenAppearance> token_appearances = TypeAnalyzer(static_cast<Type&>(token)).GetVectorOfMinimalAmountOfTokensUsedDefiningThisType();
		for(TokenAppearance token_appearance : token_appearances)
			for(unsigned token_count = 1; token_count <= token_appearance.token_count; token_count++)
			{
				if (token_appearance.token->TokenType.has_flag(TokenType_t::vector))
					cases += MakeVectorVisit(*token_appearance.token, token_count);
				else
					cases += MakeDefaultVisit(*token_appearance.token, token_count);
			}
	}

	cases += "}\n";
	return cases;
}

std::string deamer::AstVisitorBuilder::AstDefaultVisitorFormatter::MakeDefaultVisit(const Token& token,
	unsigned token_count)
{
    if (token.TokenPermission.has_flag(TokenPermission_t::node))
        return "";
    else
        return	"    if (ast_node." + token.TokenName + std::to_string(token_count) + "_ != nullptr)\n"
			"    {\n"
			"        ast_node." + token.TokenName + std::to_string(token_count) + "_->Accept(*this);\n"
			"    }\n";
}

std::string deamer::AstVisitorBuilder::AstDefaultVisitorFormatter::MakeVectorVisit(const Token& token,
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

void deamer::AstVisitorBuilder::AstDefaultVisitorFormatter::FinishVisitor()
{
	header_file_ += header_file_class_forward_declarations_ + "\n" + 
					header_file_class_definition_ + header_file_visit_prototypes_ + 
					"    };\n"
					"}\n"
					"#endif //ASTNODES_ASTVISITOR_ASTVISITOR_H\n";
	source_file_dispatch_ += "    }\n"
							 "}\n"
							 "\n";
	source_file_ += source_file_visit_functions + source_file_dispatch_;
	
	WriteOutputToFile("./AstNodes/AstVisitor/" + language_name_ + "_AstVisitor.cpp", source_file_);
	WriteOutputToFile("./AstNodes/AstVisitor/" + language_name_ + "_AstVisitor.h", header_file_);
}

std::string deamer::AstVisitorBuilder::AstDefaultVisitorFormatter::visit_function_prototype(Token& token)
{
    return "Visit(" + CreateAstNodeClassName(token) + "& ast_node)";
}

std::string deamer::AstVisitorBuilder::AstDefaultVisitorFormatter::CreateAstNodeClassName(Token& token)
{
    if (token.TokenType.has_flag(TokenType_t::start))
        return "AstTree_" + token.TokenName;
    else
        return "AstNode_" + token.TokenName;
}
