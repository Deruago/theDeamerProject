/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -July 2020 Thimo B�hmer
 * -August 2020 Thimo B�hmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEDEFINITIONPRINTER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEDEFINITIONPRINTER_H
#include "Deamer/LanguageAnalyzer/LanguageVisitor/LanguageDefinitionVisitor.h"
#include <vector>
#include <string>

namespace deamer
{
	class LanguageDefinition;

	class LanguageDefinitionPrinter : public LanguageDefinitionVisitor
	{
	protected:
		std::string MakeIndent(unsigned indent) const;
		std::string MakeIndentation(unsigned depth, unsigned indent) const;
		void PrintAllTokens(LanguageDefinition& language_definition) const;
	public:
		LanguageDefinitionPrinter() = default;
		~LanguageDefinitionPrinter() = default;

		virtual void visit(Token& visited_type);
		void first_visit(Rule& visited_type) override;
		void first_visit(Node& visited_type) override;
		void first_visit(Type& visited_type) override;
		void visit(Type& type) override;
		void visit(Node& node) override;
		
		virtual void Print(LanguageDefinition& language_definition);
		void PrintAllRules(LanguageDefinition& language_definition) const;
		void PrintAllNodes(LanguageDefinition& language_definition) const;
		void PrintAllGroupedTypes(LanguageDefinition& language_definition) const;
		void PrintAllIgnoredNodes(LanguageDefinition& language_definition) const;
		void PrintAllIgnoredTypes(LanguageDefinition& language_definition) const;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEDEFINITIONPRINTER_H