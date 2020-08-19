/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstFormatter/AstNodeSourceFormatter.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/TypeAnalyzer.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/Datastructures/TokenAppearance.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"

deamer::AstNodeSourceFormatter::AstNodeSourceFormatter(Token* token, std::string language_name) : AstFileFormatter::AstFileFormatter(token, language_name)
{
}

std::string deamer::AstNodeSourceFormatter::MakeAstFile() const
{
    std::string ast_file = MakeIncludeSectionSourceClassDefinitionDependency() +
				           MakeIncludeSectionSourceAstDependencies() +
				           MakeIncludeSectionSourceSystemDependencies() +
				           MakeAstSourceImplementation();
    return ast_file;
}

std::string deamer::AstNodeSourceFormatter::MakeAstSourceImplementation() const
{
	std::string ast_node_implementation =
		MakeBaseConstructor() +
		MakeAstNodeConstructor() +
		MakeGeneralConstructor() +
		MakeSpecificConstructors() +
		MakeGetAstIdFunction() +
        MakeInterpreterFunction();
	return ast_node_implementation;
}

std::string deamer::AstNodeSourceFormatter::MakeGetAstIdFunction() const
{
	return MakeFunction(MakeGetAstIdPrototype(),
      	   MakeGetAstIdImplementation());
}

std::string deamer::AstNodeSourceFormatter::MakeGetAstIdImplementation() const
{
	return "    return (unsigned int)" + language_name_ + "::" + MakeClassName() + "::AstType" + ";\n";
}

std::string deamer::AstNodeSourceFormatter::MakeBaseConstructor() const
{
	return MakeAstConstructorSpecificFunction(MakeConstructorNameWithLanguageNamespace() +
		"(bool isNode, std::string astNodeName)");
}

std::string deamer::AstNodeSourceFormatter::MakeGeneralConstructor() const
{
	return MakeAstConstructorGeneralFunction(MakeConstructorNameWithLanguageNamespace() +
		"(std::vector<deamer::AstNode*> astNodes)");
}

std::string deamer::AstNodeSourceFormatter::MakeInterpreterFunction() const
{
	return MakeFunction(MakeInterpreterFunctionPrototype(), MakeInterpreterImplementation());
}

std::string deamer::AstNodeSourceFormatter::MakeInterpreterTypeNullPointerGuard(const Token* token, const unsigned i) const
{
	return MakeIndentation(1) + "if (" + MakeFieldNameOfType(token, i) + " != nullptr)\n" +
		   MakeIndentation(1) + "{\n";
}

std::string deamer::AstNodeSourceFormatter::MakeInterpreterImplementation() const
{
	std::string complete_interpreter_implementation;
	if(token_->TokenPermission.has_flag(TokenPermission_t::node))
		return "";

	auto token_appearances = TypeAnalyzer(static_cast<Type&>(*token_)).GetVectorOfMinimalAmountOfTokensUsedDefiningThisType();
	for(TokenAppearance token_appearance : token_appearances)
		complete_interpreter_implementation += MakeInterpreterType(token_appearance);

	return complete_interpreter_implementation;
}

std::string deamer::AstNodeSourceFormatter::MakeInterpreterType(TokenAppearance token_appearance) const
{
	std::string interpreter_implementation;
	for(unsigned i = 1; i <= token_appearance.token_count; i++)
	{
		interpreter_implementation += MakeInterpreterTypeNullPointerGuard(token_appearance.token, i);
		if (token_appearance.token->TokenType.has_flag(TokenType_t::vector))
			interpreter_implementation += MakeSingleVectorisedInterpreteredType(token_appearance.token, i);
		else
			interpreter_implementation += MakeStandardInterpreterTypeImplementation(token_appearance.token, i);
		interpreter_implementation += MakeIndentation(1) + "}\n";
	}
	return interpreter_implementation;
}

std::string deamer::AstNodeSourceFormatter::MakeSingleVectorisedInterpreteredType(const Token* token, const unsigned count_token) const
{
	return MakeIndentation(2) + "for(" + MakeClassName(token) + "* " + token->TokenName + " : " + MakeFieldNameOfType(token, count_token) + ")\n" +
		   MakeIndentation(2) + "{\n" +
		   MakeIndentation(3) + token->TokenName + "->Generate(ast_context);\n" +
		   MakeIndentation(2) + "}\n";
}

std::string deamer::AstNodeSourceFormatter::MakeAstNodeConstructor() const
{
	return MakeAstConstructorAstInformationFunction(MakeConstructorNameWithLanguageNamespace() +
		"(deamer::AstInformation* astInformation)");
}