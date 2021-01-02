/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
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
			
			std::string CreateAstNodeClassName(Token& token);
			std::string visit_function_prototype(Token& token);
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
