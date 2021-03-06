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

#ifndef DEAMER_ASTGEN_ASTFORMATTER_ASTFILEFORMATTER_H
#define DEAMER_ASTGEN_ASTFORMATTER_ASTFILEFORMATTER_H
#include <string>
#include <vector>

namespace deamer
{
	class Rule;
	class Token;

	class AstFileFormatter
	{
	private:
		unsigned depth;
		unsigned indent_size = 4;

		std::string MakeIndent() const;

	protected:
		Token* token_;
		std::string language_name_;
		
		std::string MakeIndentation() const;
		std::string MakeIndentation(unsigned depth_) const;

		std::string MakeIncludeHeader(const std::string& header_path) const;
		std::string MakeSystemIncludeHeader(const std::string& header_path) const;

		std::string MakeSystemNamespace(const std::string& cs) const;
		
		std::string MakeConstructorNameWithLanguageNamespace() const;
		std::string MakeClassName() const;
		std::string MakeConstructorName() const;
		std::string IsTokenNodeString() const;
		std::string MakeClassName(const Token* token) const;
		std::string MakeFieldNameOfType(const Token* token, const unsigned count_token) const;
		std::string MakeArgumentNameOfType(const Token* token, const unsigned count_token) const;
		std::string MakeConstructorArgumentFromToken(Token* token, const std::vector<Token*>& visited_tokens) const;
		std::string MakeConstructorFunctionArgumentsFromProductionRule(Rule* rule) const;
		unsigned CountTokenInVector(deamer::Token* token, const std::vector<deamer::Token*>& visited_tokens) const;

		std::string MakeGetAstIdPrototype() const;
		std::string MakeInterpreterFunctionPrototype() const;
		std::string MakeVisitorFunctionPrototype() const;

		std::string MakeSpecificConstructorPrototypeWithPath(deamer::Rule* rule) const;
		std::string MakeSpecificConstructorPrototype(deamer::Rule* rule) const;
		std::string MakeSpecificConstructorPrototypeWithBaseConstructorImplementations(Rule* rule) const;
		
		// i.e sub::ctor() : base_1(), base_2()...
		std::string MakeCtorImplementationsForAstInformation() const;
		std::string MakeSpecificConstructorImplementation(Rule* rule) const;
		std::string MakeSpecificConstructors() const;
		std::string MakeCtorImplementationsForSpecificCtor() const;
		std::string MakeCtorImplementationsForGeneralCtor() const;
		std::string MakeStandardInterpreterTypeImplementation(const Token* token, const unsigned count_token) const;

		std::string MakeAstConstructorFunction(const std::string& constructor_prototype) const;
		std::string MakeAstConstructorFunction(const std::string& constructor_prototype,
			const std::string& constructor_function_implementation) const;
		std::string MakeAstConstructorAstInformationFunction(const std::string& constructor_prototype) const;
		std::string MakeAstConstructorAstInformationFunction(const std::string& constructor_prototype,
			const std::string& constructor_function_implementation) const;

		std::string MakeAstConstructorGeneralFunction(const std::string& constructor_prototype) const;
		std::string MakeAstConstructorGeneralFunction(const std::string& constructor_prototype,
			const std::string& constructor_function_implementation) const;

		std::string MakeAstConstructorSpecificFunction(const std::string& constructor_prototype) const;
		std::string MakeAstConstructorSpecificFunction(const std::string& constructor_prototype,
			const std::string& constructor_function_implementation) const;

		std::string MakeFunction(const std::string& function_prototype) const;
		std::string MakeFunction(const std::string& function_prototype, const std::string& function_implementation) const;
		std::string MakeFunctionImplementation(const std::string& cs) const;

		std::string MakeEmptyFunction(const std::string& function_prototype) const;

		std::string MakeCurrentTreeHeaderDeclaration() const;
		std::string MakeSetCurrentTreeHeaderDeclaration() const;
		std::string MakeCurrentTreeDeclaration() const;
		std::string MakeSetTree() const;
	public:
		AstFileFormatter(Token* token, std::string& language_name);
		virtual ~AstFileFormatter() = default;

		virtual std::string MakeAstFile() const = 0;
		std::string AstTreeClassDefinitionClassDependency() const;
		std::string AstNodeClassDefinitionClassDependency() const;
		std::string MakeIncludeSectionSourceClassDefinitionDependency() const;
		std::string AstClassDefinitionClassDependency() const;
		std::string MakeIncludeSectionSourceAstDependencies() const;
		std::string MakeIncludeSectionHeaderAstDependencies() const;
		std::string MakeForwardDeclaration(deamer::Token* token_unique) const;
		std::string MakeSystemForwardDeclaration(const std::string& class_name) const;
		std::string MakeForwardDeclarationSectionHeaderAstDependencies() const;
		std::string MakeSystemStandardLibraryIncludeHeader(const std::string& header_path) const;
		std::string MakeIncludeSectionSourceSystemDependencies() const;
		std::string MakeIncludeSectionHeaderSystemDependencies() const;
		std::string MakeForwardDeclarationSectionHeaderSystemDependencies() const;
	};
}

#endif //DEAMER_ASTGEN_ASTFORMATTER_ASTFILEFORMATTER_H