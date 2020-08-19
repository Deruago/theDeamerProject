/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTVISITORSECTION_H
#define DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTVISITORSECTION_H

#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstVisitor/AstDefaultVisitorFormatter.h"
#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstVisitor/AstPrinterVisitorFormatter.h"

namespace deamer {
	class Token;
	
	namespace AstVisitorBuilder {
		class AstVisitorSection
		{
		private:
			AstDefaultVisitorFormatter ast_default_visitor_formatter_ = AstDefaultVisitorFormatter("");
			AstPrinterVisitorFormatter ast_printer_visitor_formatter_ = AstPrinterVisitorFormatter("");
		protected:
		public:
			AstVisitorSection(const std::string& language_name);
			~AstVisitorSection() = default;

			void CreateAstVisitorSection();
			void AddToken(Token& token);
			void FinishAstVisitorSection();
		};
	}
}

#endif //DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTVISITORSECTION_H