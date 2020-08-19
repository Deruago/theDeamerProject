/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTNODESOURCEFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTNODESOURCEFORMATTER_H
#include <vector>

#include "Deamer/AstGen/AstFileFormatter.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/Datastructures/TokenAppearance.h"

namespace deamer
{
	class Rule;

	class AstNodeSourceFormatter : public AstFileFormatter
	{
	private:
		
		std::string MakeAstSourceImplementation() const;
		std::string MakeGetAstIdImplementation() const;
		
		std::string MakeBaseConstructor() const;
		std::string MakeGetAstIdFunction() const;
		std::string MakeGeneralConstructor() const;

		std::string MakeAstNodeConstructor() const;

		std::string MakeInterpreterFunction() const;
		std::string MakeInterpreterTypeNullPointerGuard(const Token* token, unsigned i) const;
		std::string MakeInterpreterType(TokenAppearance token_appearance) const;
		std::string MakeInterpreterImplementation() const;
		
		std::string MakeSingleVectorisedInterpreteredType(const Token* token, const unsigned count_token) const;
	protected:
	public:
		AstNodeSourceFormatter(Token* token, std::string language_name);
		~AstNodeSourceFormatter() = default;
		std::string MakeAstFile() const override;
	};
}

#endif //DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTNODESOURCEFORMATTER_H