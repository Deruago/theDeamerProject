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