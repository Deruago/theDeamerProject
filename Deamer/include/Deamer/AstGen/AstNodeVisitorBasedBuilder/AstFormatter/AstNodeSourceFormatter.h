/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEVisitorBASEDBUILDER_ASTFORMATTER_ASTNODESOURCEFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEVisitorBASEDBUILDER_ASTFORMATTER_ASTNODESOURCEFORMATTER_H
#include <vector>

#include "Deamer/AstGen/AstFileFormatter.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/Datastructures/TokenAppearance.h"

namespace deamer { namespace AstVisitorBuilder {

	class AstNodeSourceFormatter : public AstFileFormatter
	{
	private:
		std::string MakeAstSourceImplementation() const;
		std::string MakeGetAstIdImplementation() const;
		
		std::string MakeBaseConstructor() const;
		std::string MakeGetAstIdFunction() const;
		std::string MakeGeneralConstructor() const;

		std::string MakeAstNodeConstructor() const;

		std::string MakeVisitorFunction() const;
		std::string MakeVisitorImplementation() const;
	public:
		AstNodeSourceFormatter(Token* token, std::string language_name);
		~AstNodeSourceFormatter() = default;
		std::string MakeAstFile() const override;
	};
}}

#endif //DEAMER_ASTGEN_ASTNODEVisitorBASEDBUILDER_ASTFORMATTER_ASTNODESOURCEFORMATTER_H