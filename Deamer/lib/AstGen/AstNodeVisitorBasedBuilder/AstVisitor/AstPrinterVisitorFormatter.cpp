/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
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
	header_file_ =	"#ifndef ASTNODES_ASTVISITOR_ASTVISITOR_H\n"
					"\n"
					"/* This is an system generated AstPrinter. We recommend not changing code in this file\n"
					"   If you have improvements, make an pull request.\n"
	                "   If you have suggestions, make an issue or contact a developer or maintainer.\n"
					"*/\n\n"
					"#define ASTNODES_ASTVISITOR_ASTVISITOR_H\n"
					"\n"
					"#include <Deamer/AstGen/AstVisitor.h>\n"
					"\n"
					"namespace " + language_name_ + "\n"
					"{\n";

	header_file_class_definition_ = "    class " + language_name_ + "_AstVisitor : public AstVisitor\n"
									"    {\n"
									"    private:\n"
									"    protected:\n"
									"    public:\n"
									"        " + language_name_ + "_AstVisitor() = Printer;\n"
									"        void Dispatch(AstNode& ast_node) override;\n"
									"\n";

	source_file_ =	"#include \"./" + language_name_ + "_AstVisitor.h\"\n"
					"#include \"AstEnum.h\"\n"
					"#include \"AstNodes.h\"\n"
					"#include <iostream>\n"
					"\n";

	source_file_dispatch_ = "void " + language_name_ + "::" + language_name_ + "_AstVisitor::Dispatch(AstNode& ast_node)\n"
							"{\n"
							"    switch(ast_node.GetAstId())\n"
							"    {\n";
}

void deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::AddToken(Token& token)
{
	source_file_dispatch_ += "    case " + language_name_ + "::AstEnum_t::" + token.TokenName + ":\n"
		"        Visit(static_cast<AstNode_" + token.TokenName + "&>(ast_node));\n"
		"        break;\n";
	source_file_visit_functions += MakeAdditionToSourceFile(token) + "\n";
}

std::string deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::MakeAdditionToSourceFile(Token& token)
{
	if (token.TokenType.has_flag(TokenType_t::start))
		header_file_class_forward_declarations_ += "    class AstTree_" + token.TokenName + ";\n";
	else
		header_file_class_forward_declarations_ += "    class AstNode_" + token.TokenName + ";\n";

	header_file_visit_prototypes_ += "        void Visit(AstNode_" + token.TokenName + "& ast_node);\n";

	std::string cases;
	cases += "void " + language_name_ + "::" + language_name_ + "_AstVisitor::Visit(AstNode_" + token.TokenName + "& ast_node)\n";
	cases += "{\n";
	cases += PrintAstNode(token) + "\n";
	if (token.TokenPermission.has_flag(TokenPermission_t::node))
	{
		cases += MakePrinterVisit(token, 1);
	}
	else
	{
		std::vector<TokenAppearance> token_appearances = TypeAnalyzer(static_cast<Type&>(token)).GetVectorOfMinimalAmountOfTokensUsedDefiningThisType();
		for (TokenAppearance token_appearance : token_appearances)
			for (unsigned token_count = 1; token_count <= token_appearance.token_count; token_count++)
			{
				if (token_appearance.token->TokenType.has_flag(TokenType_t::vector))
					cases += MakeVectorVisit(*token_appearance.token, token_count);
				else
					cases += MakePrinterVisit(*token_appearance.token, token_count);
			}
	}

	cases += "}\n";
	return cases;
}

std::string deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::MakePrinterVisit(const Token& token,
	unsigned token_count)
{
	return	"    if (ast_node." + token.TokenName + std::to_string(token_count) + " != nullptr)\n"
			"    {\n"
			"        ast_node." + token.TokenName + std::to_string(token_count) + "->Accept(*this);\n"
			"    }\n";
}

std::string deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::MakeVectorVisit(const Token& token,
	unsigned token_count)
{
	return	"    if (ast_node." + token.TokenName + std::to_string(token_count) + " != nullptr)\n"
			"    {\n"
			"        for(AstNode_" + token.TokenName + " " + token.TokenName + " : ast_node." + token.TokenName + std::to_string(token_count) + ")\n"
			"        {\n"
			"            " + token.TokenName + "->Accept(*this);\n"
			"        }\n"
			"    }\n";
}

std::string deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::PrintAstNode(const Token& token)
{
	return "    std::cout << \"" + token.TokenName + "\" << std::endl;\n";
}

void deamer::AstVisitorBuilder::AstPrinterVisitorFormatter::FinishVisitor()
{
	header_file_ += header_file_class_forward_declarations_ + "\n" +
		header_file_class_definition_ + header_file_visit_prototypes_ +
		"    }\n"
		"}\n"
		"#endif //ASTNODES_ASTVISITOR_ASTVISITOR_H\n";
	source_file_dispatch_ += "    }\n"
		"}\n"
		"\n";
	source_file_ += source_file_visit_functions + source_file_dispatch_;

	WriteOutputToFile("./AstNodes/AstVisitor/" + language_name_ + "_AstPrinter.cpp", source_file_);
	WriteOutputToFile("./AstNodes/AstVisitor/" + language_name_ + "_AstPrinter.h", header_file_);
}
