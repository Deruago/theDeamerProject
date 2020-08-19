#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstNodeSectionFormatter.h"
#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstFormatter/AstFileFormatterFactory.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstFileType.h"
#include <memory>


deamer::AstInterpreterBuilder::AstNodeSectionFormatter::AstNodeSectionFormatter(const std::string& language_name) : AstNodeFormatter(language_name)
{
}

void deamer::AstInterpreterBuilder::AstNodeSectionFormatter::MakeAstNode(Token* token, AstFileType ast_file_type)
{
	const std::unique_ptr<AstFileFormatter> formatter = AstFileFormatterFactory().MakeAstFileFormatter(token, language_name_, ast_file_type);
	output += formatter->MakeAstFile();
}

void deamer::AstInterpreterBuilder::AstNodeSectionFormatter::MakeAstTree(Token* token, AstFileType ast_file_type)
{
	const std::unique_ptr<AstFileFormatter> formatter = AstFileFormatterFactory().MakeAstFileFormatter(token, language_name_, ast_file_type);
	output += formatter->MakeAstFile();
}