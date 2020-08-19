/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstFormatter/AstFileFormatterFactory.h"
#include "Deamer/AstGen/AstFileFormatter.h"
#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstFormatter/AstNodeHeaderFormatter.h"
#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstFormatter/AstNodeSourceFormatter.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstFileType.h"

std::unique_ptr<deamer::AstFileFormatter> deamer::AstFileFormatterFactory::MakeAstFileFormatter(Token* token, const std::string
                                                                                                & language_name,
	AstFileType ast_file_type) const
{
	switch (ast_file_type)
	{
	case AstFileType::header:
		return std::make_unique<AstNodeHeaderFormatter>(token, language_name);
	case AstFileType::source:
		return std::make_unique<AstNodeSourceFormatter>(token, language_name);
	}
	return std::make_unique<AstNodeSourceFormatter>(token, language_name);
}
