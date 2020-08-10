/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Böhmer 2020
 *
 * Modified:
 * -August 2020 Thimo Böhmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_TOKENPRINTER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_TOKENPRINTER_H
#include "Deamer/LanguageAnalyzer/LanguagePrinter/LanguageDefinitionPrinter.h"

namespace deamer
{
	class TokenPrinter : LanguageDefinitionPrinter
	{
	private:
	protected:
	public:
		TokenPrinter() = default;
		~TokenPrinter() = default;

		void visit(Token & visited_type) override;
		void first_visit(Rule & visited_type) override;
		void first_visit(Node & visited_type) override;
		void first_visit(Type & visited_type) override;
		void visit(Type & type) override;
		void visit(Node& node) override;

		void Print(LanguageDefinition & language_definition) override;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_TOKENPRINTER_H