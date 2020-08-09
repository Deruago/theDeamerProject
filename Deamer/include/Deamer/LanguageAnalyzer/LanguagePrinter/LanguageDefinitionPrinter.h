/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -July 2020 Thimo Böhmer
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEDEFINITIONPRINTER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEDEFINITIONPRINTER_H
#include <vector>
#include <string>

namespace deamer
{
	class LanguageDefinition;
	class Token;
	class Type;
	class Rule;

	class LanguageDefinitionPrinter
	{
	public:
		LanguageDefinitionPrinter() = default;
		~LanguageDefinitionPrinter() = default;

		void PrintCompleteToken(Token* token, unsigned indent) const;
		void PrintCompleteRule(std::vector<Type*>& visited_types, Rule* rule, unsigned indent) const;
		void PrintCompleteType(Type* type, unsigned indent) const;
		void PrintTree(LanguageDefinition& language_definition) const;
		bool TypeAlreadyVisited(const std::vector<Type*>& visited_types, Token* new_type) const;
		std::string MakeIndent(unsigned indent) const;
		std::string MakeIndentation(unsigned depth, unsigned indent) const;
		void PrintCompleteType(std::vector<Type*> visited_types, Type* type, unsigned indent) const;
		void PrintAllTokens(LanguageDefinition& language_definition) const;
		void PrintAllRules(LanguageDefinition& language_definition) const;
		void PrintAllNodes(LanguageDefinition& language_definition) const;
		void PrintAllGroupedTypes(LanguageDefinition& language_definition) const;
		void PrintAllIgnoredNodes(LanguageDefinition& language_definition) const;
		void PrintAllIgnoredTypes(LanguageDefinition& language_definition) const;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEDEFINITIONPRINTER_H