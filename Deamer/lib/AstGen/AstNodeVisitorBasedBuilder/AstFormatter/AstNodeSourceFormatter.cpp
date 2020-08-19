/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstFormatter/AstNodeSourceFormatter.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/TypeAnalyzer.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/Datastructures/TokenAppearance.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"

deamer::AstVisitorBuilder::AstNodeSourceFormatter::AstNodeSourceFormatter(Token* token, std::string language_name) : AstFileFormatter::AstFileFormatter(token, language_name)
{
}

std::string deamer::AstVisitorBuilder::AstNodeSourceFormatter::MakeAstFile() const
{
    std::string ast_file = MakeIncludeSectionSourceClassDefinitionDependency() +
				           MakeIncludeSectionSourceAstDependencies() +
				           MakeIncludeSectionSourceSystemDependencies() +
						   MakeSystemIncludeHeader("Deamer/AstGen/AstVisitor") +
						   MakeCurrentTreeDeclaration() +
				           MakeAstSourceImplementation();
    return ast_file;
}

std::string deamer::AstVisitorBuilder::AstNodeSourceFormatter::MakeAstSourceImplementation() const
{
	std::string ast_node_implementation =
		MakeBaseConstructor() +
		MakeAstNodeConstructor() +
		MakeGeneralConstructor() +
		MakeSpecificConstructors() +
		MakeGetAstIdFunction() +
		MakeSetTree() +
        MakeVisitorFunction();
	return ast_node_implementation;
}

std::string deamer::AstVisitorBuilder::AstNodeSourceFormatter::MakeGetAstIdFunction() const
{
	return MakeFunction(MakeGetAstIdPrototype(),
      	   MakeGetAstIdImplementation());
}

std::string deamer::AstVisitorBuilder::AstNodeSourceFormatter::MakeGetAstIdImplementation() const
{
	return "    return (unsigned int)" + language_name_ + "::" + MakeClassName() + "::AstType" + ";\n";
}

std::string deamer::AstVisitorBuilder::AstNodeSourceFormatter::MakeBaseConstructor() const
{
	return MakeAstConstructorSpecificFunction(MakeConstructorNameWithLanguageNamespace() +
		"(bool isNode, std::string astNodeName)");
}

std::string deamer::AstVisitorBuilder::AstNodeSourceFormatter::MakeGeneralConstructor() const
{
	return MakeAstConstructorGeneralFunction(MakeConstructorNameWithLanguageNamespace() +
		"(std::vector<deamer::AstNode*> astNodes)");
}

std::string deamer::AstVisitorBuilder::AstNodeSourceFormatter::MakeVisitorFunction() const
{
	return MakeFunction(MakeVisitorFunctionPrototype(), MakeVisitorImplementation());
}

std::string deamer::AstVisitorBuilder::AstNodeSourceFormatter::MakeVisitorImplementation() const
{
	return MakeIndentation(1) + "ast_visitor.Dispatch(*this);\n";
}

std::string deamer::AstVisitorBuilder::AstNodeSourceFormatter::MakeAstNodeConstructor() const
{
	return MakeAstConstructorAstInformationFunction(MakeConstructorNameWithLanguageNamespace() +
		"(deamer::AstInformation* astInformation)");
}