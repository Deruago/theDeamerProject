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

#ifndef DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTNODEHEADERFORMATTER_H
#define DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTNODEHEADERFORMATTER_H
#include <iosfwd>
#include <vector>


#include "Deamer/AstGen/AstFileFormatter.h"
#include "Deamer/LanguageAnalyzer/LanguageAnalyzer/Datastructures/TokenAppearance.h"

namespace deamer { namespace AstInterpreterBuilder {
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
		~AstNodeHeaderFormatter() = default;
		std::string MakeHeaderGuardMacro() const;
		std::string MakeHeaderGuardBegin() const;
		std::string MakeHeaderGuardEnd() const;
		std::string MakeHeaderPrivateSection() const;
		std::string MakeHeaderSpecificConstructorPrototypes() const;
		std::string MakeHeaderPrototype(const std::string& prototype) const;
		std::string MakeHeaderProtectedSection() const;
		std::string MakeHeaderPublicSection() const;
		std::string InheritFromBaseClassInClassDefinition(Token* token) const;
		std::string MakeClassSubclass() const;
		std::string MakeHeaderClassDefinition() const;
		std::string MakeHeaderNamespace(const std::string& cs) const;
		std::string MakeAstFile() const override;
	};
}}

#endif //DEAMER_ASTGEN_ASTNODEINTERPRETERBASEDBUILDER_ASTFORMATTER_ASTNODEHEADERFORMATTER_H