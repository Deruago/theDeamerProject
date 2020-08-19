/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTDEFAULTVISITORFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTDEFAULTVISITORFORMATTER_H

#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstVisitor/AstVisitorFormatter.h"
#include <string>

namespace deamer {
	class Token;
	namespace AstVisitorBuilder {

		class AstDefaultVisitorFormatter : public AstVisitorFormatter
		{
		private:
			std::string language_name_;
			std::string header_file_;
			std::string source_file_;
			std::string source_file_visit_functions;
			std::string source_file_dispatch_;
			std::string header_file_visit_prototypes_;
			std::string header_file_class_definition_;
			std::string header_file_class_forward_declarations_;

			std::string MakeDefaultVisit(const Token& token, unsigned token_count);
			std::string MakeVectorVisit(const Token& token, unsigned token_count);
			std::string MakeAdditionToSourceFile(Token& token);
		protected:
		public:
			AstDefaultVisitorFormatter(const std::string& language_name);
			~AstDefaultVisitorFormatter() = default;

			void CreateVisitor();
			void AddToken(Token& token);
			void FinishVisitor();
		};
	}
}

#endif //DEAMER_ASTGEN_ASTNODEVISITORBASEDBUILDER_ASTVISITOR_ASTDEFAULTVISITORFORMATTER_H