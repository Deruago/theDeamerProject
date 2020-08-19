/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstBuilderInterpreterBased.h"
#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstNodeSectionFormatter.h"
//#include "Deamer/FileBuilder/HFileBuilder/HFClassBuilder.h"
//#include "Deamer/FileBuilder/Types/FileNamespaceSection.h"
#include "Deamer/FileBuilder/Types/FileClassSection.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Type.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Rule.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Node.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstFileType.h"

deamer::AstInterpreterBuilder::AstBuilderInterpreterBased::AstBuilderInterpreterBased(const std::string& directory, const std::string
                                                                                      & language_name) : AstBuilder(directory, language_name)
{
    enum_header_section_formatter_ = AstEnumHeaderSectionFormatter(directory, language_name);
    global_header_formatter_ = AstGlobalHeaderFormatter(directory, language_name);
}

void deamer::AstInterpreterBuilder::AstBuilderInterpreterBased::StartBuild()
{
    enum_header_section_formatter_.CreateAstNodeEnumFile();
    global_header_formatter_.CreateGlobalHeaderFile();
}

void deamer::AstInterpreterBuilder::AstBuilderInterpreterBased::Build(Node& node)
{
    WriteOutputToFile(AstNodeFormatter().MakeClassName(&node) + ".cpp", FillAstSourceFile(&node));
    WriteOutputToFile(AstNodeFormatter().MakeClassName(&node) + ".h", FillAstHeaderFile(&node));
    enum_header_section_formatter_.AddToken(node);
    global_header_formatter_.AddToken(node);
}

void deamer::AstInterpreterBuilder::AstBuilderInterpreterBased::Build(Type& type)
{
    WriteOutputToFile(AstNodeFormatter().MakeClassName(&type) + ".cpp", FillAstSourceFile(&type));
    WriteOutputToFile(AstNodeFormatter().MakeClassName(&type) + ".h", FillAstHeaderFile(&type));
    enum_header_section_formatter_.AddToken(type);
    global_header_formatter_.AddToken(type);
}

void deamer::AstInterpreterBuilder::AstBuilderInterpreterBased::FinishBuild()
{
    enum_header_section_formatter_.FinishAstNodeEnumFile();
    global_header_formatter_.FinishGlobalHeaderFile();
}

std::string deamer::AstInterpreterBuilder::AstBuilderInterpreterBased::FillAstSourceFile(Token* token) const
{
    AstNodeSectionFormatter formatter = AstNodeSectionFormatter(language_name_);
    formatter.MakeAstNode(token, AstFileType::source);
    return formatter.output;
}

std::string deamer::AstInterpreterBuilder::AstBuilderInterpreterBased::FillAstHeaderFile(Token* token) const
{
    AstNodeSectionFormatter formatter = AstNodeSectionFormatter(language_name_);
    formatter.MakeAstNode(token, AstFileType::header);
    return formatter.output;
}

deamer::FileClassSection* deamer::AstInterpreterBuilder::AstBuilderInterpreterBased::GetAstNodeFileBuilderClass() const
{
    return _AstNode;
}