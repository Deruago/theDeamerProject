/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
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

		std::string MakeIncludeHeader(const std::string& header_path) const;
		std::string MakeSystemIncludeHeader(const std::string& header_path) const;
	protected:
		Token* token_;
		std::string language_name_;
		
		std::string MakeIndentation() const;
		std::string MakeIndentation(unsigned depth_) const;


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
	public:
		AstFileFormatter(Token* token, std::string& language_name);
		virtual ~AstFileFormatter() = default;

		virtual std::string MakeAstFile() const = 0;
		std::string AstTreeClassDefinitionClassDependency() const;
		std::string AstNodeClassDefinitionClassDependency() const;
		std::string MakeIncludeSectionSourceClassDefinitionDependency() const;
		std::string MakeIncludeSectionSourceAstDependencies() const;
		std::string MakeIncludeSectionHeaderAstDependencies() const;
		std::string MakeForwardDeclarationSectionHeaderAstDependencies() const;
		std::string MakeIncludeSectionSourceSystemDependencies() const;
		std::string MakeIncludeSectionHeaderSystemDependencies() const;
		std::string MakeForwardDeclarationSectionHeaderSystemDependencies() const;
	};
}

#endif //DEAMER_ASTGEN_ASTFORMATTER_ASTFILEFORMATTER_H