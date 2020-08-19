/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEVisitorBASEDBUILDER_ASTFORMATTER_ASTNODEHEADERFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEVisitorBASEDBUILDER_ASTFORMATTER_ASTNODEHEADERFORMATTER_H
#include <iosfwd>
#include <vector>


#include "Deamer/AstGen/AstFileFormatter.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/Datastructures/TokenAppearance.h"

namespace deamer { namespace AstVisitorBuilder {
	class AstNodeHeaderFormatter : public AstFileFormatter
	{
	private:
		std::string MakeStringAllCaps(std::string cs) const;

		std::string MakeSystemRequiredFields() const;
		std::string MakeClassFieldType(const TokenAppearance& token_appearance) const;
		std::string MakeHeaderField(const std::string& cs) const;
		std::string MakeFieldsFromTokenAppearance(const TokenAppearance& token_appearance) const;
		std::string MakeSpecificConstructorFields() const;
		std::string MakeClassFieldName(const deamer::TokenAppearance& token_appearance, unsigned i) const;

		std::string MakeHeaderAstInformationPrototype() const;
		std::string MakeHeaderGeneralPrototype() const;
		std::string MakeHeaderBasePrototype() const;
		std::string MakeHeaderAstIdPrototype() const;

		std::string MakeHeaderSystemPrototypes() const;
	protected:
	public:
		AstNodeHeaderFormatter(Token* token, std::string language_name);
		std::string MakeAstFile() const;
		~AstNodeHeaderFormatter() = default;
		std::string MakeHeaderGuardMacro() const;
		std::string MakeHeaderGuardBegin() const;
		std::string MakeHeaderGuardEnd() const;
		std::string MakeHeaderPrivateSection() const;
		std::string MakeHeaderSpecificConstructorPrototypes() const;
		std::string MakeHeaderPrototype(const std::string & prototype) const;
		std::string MakeHeaderProtectedSection() const;
		std::string MakeHeaderPublicSection() const;
		std::string InheritFromBaseClassInClassDefinition(Token * token) const;
		std::string MakeClassSubclass() const;
		std::string MakeHeaderClassDefinition() const;
		std::string MakeHeaderNamespace(const std::string & cs) const;

	};
}}

#endif //DEAMER_ASTGEN_ASTNODEVisitorBASEDBUILDER_ASTFORMATTER_ASTNODEHEADERFORMATTER_H