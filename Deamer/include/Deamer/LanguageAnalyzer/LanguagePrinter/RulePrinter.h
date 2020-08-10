/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_RULEPRINTER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_RULEPRINTER_H
#include "Deamer/LanguageAnalyzer/LanguagePrinter/LanguageDefinitionPrinter.h"

namespace deamer
{
	class RulePrinter : LanguageDefinitionPrinter
	{
	private:
	protected:
	public:
		RulePrinter() = default;
		~RulePrinter() = default;

		void visit(Token& visited_type) override;
		void visit(Rule& visited_type) override;
		void visit(Node& visited_type) override;
		void visit(Type& visited_type) override;
		void last_visit(Type& type) override;
		void last_visit(Node& node) override;

		void Print(LanguageDefinition& language_definition) override;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_RULEPRINTER_H