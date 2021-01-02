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

#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstFormatter/AstNodeSourceFormatter.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/TypeAnalyzer.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/Datastructures/TokenAppearance.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageGenConstants.h"

deamer::AstInterpreterBuilder::AstNodeSourceFormatter::AstNodeSourceFormatter(Token* token, std::string language_name) : AstFileFormatter::AstFileFormatter(token, language_name)
{
}

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeAstFile() const
{
    std::string ast_file = MakeIncludeSectionSourceClassDefinitionDependency() +
				           MakeIncludeSectionSourceAstDependencies() +
				           MakeIncludeSectionSourceSystemDependencies() +
						   MakeCurrentTreeDeclaration() +
				           MakeAstSourceImplementation();
    return ast_file;
}

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeAstSourceImplementation() const
{
	std::string ast_node_implementation =
		MakeBaseConstructor() +
		MakeAstNodeConstructor() +
		MakeGeneralConstructor() +
		MakeSpecificConstructors() +
		MakeGetAstIdFunction() +
		MakeSetTree() +
		MakeInterpreterFunction();
	return ast_node_implementation;
}

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeGetAstIdFunction() const
{
	return MakeFunction(MakeGetAstIdPrototype(),
      	   MakeGetAstIdImplementation());
}

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeGetAstIdImplementation() const
{
	return "    return (unsigned int)" + language_name_ + "::" + MakeClassName() + "::AstType" + ";\n";
}

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeBaseConstructor() const
{
	return MakeAstConstructorSpecificFunction(MakeConstructorNameWithLanguageNamespace() +
		"(bool isNode, std::string astNodeName)");
}

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeGeneralConstructor() const
{
	return MakeAstConstructorGeneralFunction(MakeConstructorNameWithLanguageNamespace() +
		"(std::vector<deamer::AstNode*> astNodes)");
}

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeInterpreterFunction() const
{
	return MakeFunction(MakeInterpreterFunctionPrototype(), MakeInterpreterImplementation());
}

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeInterpreterTypeNullPointerGuard(const Token* token, const unsigned i) const
{
	return MakeIndentation(1) + "if (" + MakeFieldNameOfType(token, i) + " != nullptr)\n" +
		   MakeIndentation(1) + "{\n";
}

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeInterpreterImplementation() const
{
	std::string complete_interpreter_implementation;
	if(token_->TokenPermission.has_flag(TokenPermission_t::node))
		return "";

	auto token_appearances = TypeAnalyzer(static_cast<Type&>(*token_)).GetVectorOfMinimalAmountOfTokensUsedDefiningThisType();
	for(TokenAppearance token_appearance : token_appearances)
		complete_interpreter_implementation += MakeInterpreterType(token_appearance);

	return complete_interpreter_implementation;
}

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeInterpreterType(TokenAppearance token_appearance) const
{
	std::string interpreter_implementation;
	//interpreter_implementation += MakeIndentation(1) + "ast_context.interpreter(this)\n";
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

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeSingleVectorisedInterpreteredType(const Token* token, const unsigned count_token) const
{
	return MakeIndentation(2) + "for(" + MakeClassName(token) + "* " + token->TokenName + " : " + MakeFieldNameOfType(token, count_token) + ")\n" +
		   MakeIndentation(2) + "{\n" +
		   MakeIndentation(3) + token->TokenName + "->Generate(ast_context);\n" +
		   MakeIndentation(2) + "}\n";
}

std::string deamer::AstInterpreterBuilder::AstNodeSourceFormatter::MakeAstNodeConstructor() const
{
	return MakeAstConstructorAstInformationFunction(MakeConstructorNameWithLanguageNamespace() +
		"(deamer::AstInformation* astInformation)");
}