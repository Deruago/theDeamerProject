/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#include "Deamer/AstGen/AstBuilderFactory.h"
#include "Deamer/AstGen/AstNodeDataStructures/AstBuilderType.h"
#include "Deamer/AstGen/AstNodeInterpreterBasedBuilder/AstBuilderInterpreterBased.h"
#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstBuilderVisitorBased.h"

std::unique_ptr<deamer::AstBuilder> deamer::AstBuilderFactory::MakeAstBuilder(AstBuilderType ast_builder_type, const std::string& directory, const std::string& language_name) const
{
	switch(ast_builder_type)
	{
	case AstBuilderType::interpreter:
		return std::make_unique<AstInterpreterBuilder::AstBuilderInterpreterBased>(directory, language_name);
	case AstBuilderType::visitor:
		return std::make_unique<AstVisitorBuilder::AstBuilderVisitorBased>(directory, language_name);
	}
	return std::make_unique<AstVisitorBuilder::AstBuilderVisitorBased>(directory, language_name);
}


