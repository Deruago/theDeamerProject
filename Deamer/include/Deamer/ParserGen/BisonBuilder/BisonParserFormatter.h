/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -July 2020 Thimo Bohmer
 */

#ifndef DEAMER_PARSERGEN_BISONBUILDER_BISONPARSERFORMATTER_H
#define DEAMER_PARSERGEN_BISONBUILDER_BISONPARSERFORMATTER_H
#include <string>

#include "Deamer/LanguageAnalyzer/LanguageOptimiser.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

namespace deamer
{
	class BisonParserFormatter
	{
	public:
		BisonParserFormatter(const std::string& lang_name, const std::string& firstType,
		                     const std::string& token_declaration_part, const std::string& type_declaration_part,
		                     const std::string& rule_declaration_part, const LanguageDefinition* language_definition);
		std::string MakeParserFile(std::ostringstream& ParserFunctions) const; // Executed last
	private:
		std::string language_name_;
		std::string first_type_name_;
		std::string include_part_;
		std::string token_declaration_part_;
		std::string type_declaration_part_;
		std::string union_declaration_part_;
		std::string part_between_union_and_rule_sections_;
		std::string rule_declaration_part_;
		const LanguageDefinition* language_definition_;

		std::string CombineParserPartsIntoOnePart(std::ostringstream& ParserFunctions) const;
		void MakeParserErrorFunction(std::ostringstream& ParserFunctions) const;
		void MakeParserDestructor(std::ostringstream& extendedFunctionPart) const;
		void MakeParserConstructor(std::ostringstream& extendedFunctionPart) const;
		void MakeParseFileLocationFunction(std::ostringstream& extendedFunctionPart) const;
		void MakeParseFileFunction(std::ostringstream& extendedFunctionPart) const;
		void MakeParseTextFunction(std::ostringstream& extendedFunctionPart) const;
		std::string MakeUnionAstNodes() const;
		std::string MakeUnion() const;
		std::string MakeInclude() const;
		std::string MakeSeperationPartBetweenUnionAndRuleParts() const;
		
		void AddTokenDeclarationPart(const std::string& token_declaration_part);
		void AddTypeDeclarationPart(const std::string& type_declaration_part);
		void AddRuleDeclarationPart(const std::string& rule_declaration_part);
	};
}

#endif //DEAMER_PARSERGEN_BISONBUILDER_BISONPARSERFORMATTER_H