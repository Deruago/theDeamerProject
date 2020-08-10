/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstFormatter/AstFileFormatterFactory.h"
#include "Deamer/AstGen/AstFormatter/AstFileFormatter.h"
#include "Deamer/AstGen/AstFormatter/AstNodeHeaderFormatter.h"
#include "Deamer/AstGen/AstFormatter/AstNodeSourceFormatter.h"
#include "Deamer/AstGen/AstFormatter/AstTreeSourceFormatter.h"
#include "Deamer/AstGen/AstFormatter/AstTreeHeaderFormatter.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstType.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstFileType.h"

std::unique_ptr<deamer::AstFileFormatter> deamer::AstFileFormatterFactory::MakeAstFileFormatter(AstType ast_type,
	AstFileType ast_file_type) const
{
	switch (ast_file_type)
	{
	case AstFileType::header:
		return MakeAstHeaderFileFormatter(ast_type);
	case AstFileType::source:
		return MakeAstSourceFileFormatter(ast_type);
	}
	return MakeAstHeaderFileFormatter(ast_type);
}

std::unique_ptr<deamer::AstFileFormatter> deamer::AstFileFormatterFactory::MakeAstSourceFileFormatter(AstType ast_type) const
{
	switch (ast_type)
	{
	case AstType::node:
		return std::make_unique<AstNodeSourceFormatter>();
	case AstType::tree:
		return std::make_unique<AstTreeSourceFormatter>();
	}
	return std::make_unique<AstNodeSourceFormatter>();
}

std::unique_ptr<deamer::AstFileFormatter> deamer::AstFileFormatterFactory::MakeAstHeaderFileFormatter(AstType ast_type) const
{
	switch (ast_type)
	{
	case AstType::node:
		return std::make_unique<AstNodeHeaderFormatter>();
	case AstType::tree:
		return std::make_unique<AstTreeHeaderFormatter>();
	}
	return std::make_unique<AstNodeHeaderFormatter>();
}
