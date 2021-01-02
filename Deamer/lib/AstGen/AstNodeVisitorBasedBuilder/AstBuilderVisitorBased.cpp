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

#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstBuilderVisitorBased.h"
#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstNodeSectionFormatter.h"
//#include "Deamer/FileBuilder/HFileBuilder/HFClassBuilder.h"
//#include "Deamer/FileBuilder/Types/FileNamespaceSection.h"
#include "Deamer/FileBuilder/Types/FileClassSection.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstFileType.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Node.h"

deamer::AstVisitorBuilder::AstBuilderVisitorBased::AstBuilderVisitorBased(const std::string& directory, const std::string
                                                                          & language_name) : AstBuilder(directory, language_name)
{	
    enum_header_section_formatter_ = AstEnumHeaderSectionFormatter(directory, language_name);
    global_header_formatter_ = AstGlobalHeaderFormatter(directory, language_name);
    ast_visitor_section_ = AstVisitorSection(language_name);
}

void deamer::AstVisitorBuilder::AstBuilderVisitorBased::StartBuild()
{
    enum_header_section_formatter_.CreateAstNodeEnumFile();
    global_header_formatter_.CreateGlobalHeaderFile();

	ast_visitor_section_.CreateAstVisitorSection();
}

void deamer::AstVisitorBuilder::AstBuilderVisitorBased::Build(Node& node)
{
    WriteOutputToFile(AstNodeFormatter().MakeClassName(&node) + ".cpp", FillAstSourceFile(&node));
    WriteOutputToFile(AstNodeFormatter().MakeClassName(&node) + ".h", FillAstHeaderFile(&node));

	enum_header_section_formatter_.AddToken(node);
    global_header_formatter_.AddToken(node);
	
    ast_visitor_section_.AddToken(node);
}

void deamer::AstVisitorBuilder::AstBuilderVisitorBased::Build(Type& type)
{
    WriteOutputToFile(AstNodeFormatter().MakeClassName(&type) + ".cpp", FillAstSourceFile(&type));
    WriteOutputToFile(AstNodeFormatter().MakeClassName(&type) + ".h", FillAstHeaderFile(&type));

	enum_header_section_formatter_.AddToken(type);
    global_header_formatter_.AddToken(type);

    ast_visitor_section_.AddToken(type);
}

void deamer::AstVisitorBuilder::AstBuilderVisitorBased::FinishBuild()
{
    enum_header_section_formatter_.FinishAstNodeEnumFile();
    global_header_formatter_.FinishGlobalHeaderFile();
	
    ast_visitor_section_.FinishAstVisitorSection();
}

std::string deamer::AstVisitorBuilder::AstBuilderVisitorBased::MakeAstNode(Token* token) const
{
    AstNodeSectionFormatter formatter = AstNodeSectionFormatter(language_name_);
    formatter.MakeAstNode(token, AstFileType::header);
    return formatter.output;
}

std::string deamer::AstVisitorBuilder::AstBuilderVisitorBased::FillAstSourceFile(Token* token) const
{
    AstNodeSectionFormatter formatter = AstNodeSectionFormatter(language_name_);
    formatter.MakeAstNode(token, AstFileType::source);
    return formatter.output;
}

std::string deamer::AstVisitorBuilder::AstBuilderVisitorBased::FillAstHeaderFile(Token* token) const
{
    AstNodeSectionFormatter formatter = AstNodeSectionFormatter(language_name_);
    formatter.MakeAstNode(token, AstFileType::header);
    return formatter.output;
}

deamer::FileClassSection* deamer::AstVisitorBuilder::AstBuilderVisitorBased::GetAstNodeFileBuilderClass() const
{
    return _AstNode;
}