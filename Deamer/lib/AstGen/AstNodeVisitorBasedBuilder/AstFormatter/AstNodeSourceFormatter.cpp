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