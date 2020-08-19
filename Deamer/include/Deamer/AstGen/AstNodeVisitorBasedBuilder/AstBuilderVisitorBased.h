/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -June 2020 Thimo Böhmer
 * -July 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTBUILDER_H
#define DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTBUILDER_H


#include "Deamer/AstGen/AstBuilder.h"
#include "Deamer/AstGen/AstEnumHeaderSectionFormatter.h"
#include "Deamer/AstGen/AstGlobalHeaderFormatter.h"
#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstVisitor/AstVisitorSection.h"


namespace deamer {
	namespace AstVisitorBuilder {

	class AstBuilderVisitorBased : public AstBuilder
	{
	private:
		AstEnumHeaderSectionFormatter enum_header_section_formatter_ = AstEnumHeaderSectionFormatter("", "");
		AstGlobalHeaderFormatter global_header_formatter_ = AstGlobalHeaderFormatter("", "");
		AstVisitorSection ast_visitor_section_ = AstVisitorSection("");

		deamer::FileClassSection* GetAstNodeFileBuilderClass() const;
		std::string MakeAstNode(Token* token) const;
		std::string FillAstSourceFile(Token* token) const;
		std::string FillAstHeaderFile(Token* token) const;
	public:
		AstBuilderVisitorBased(const std::string& directory, const std::string& language_name);
		
		void StartBuild() override;
		void Build(Node& node) override;
		void Build(Type& type) override;
		void FinishBuild() override;
	};
}}

#endif //DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTBUILDER_H