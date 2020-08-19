/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo B�hmer 2020
 *
 * Modified:
 * -August 2020 Thimo B�hmer
 */

#ifndef DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_NODEPRINTER_H
#define DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_NODEPRINTER_H
#include "Deamer/LanguageAnalyzer/LanguagePrinter/LanguageDefinitionPrinter.h"

namespace deamer
{
	class NodePrinter : LanguageDefinitionPrinter
	{
	private:
	protected:
	public:
		NodePrinter() = default;
		~NodePrinter() = default;

		void visit(Token& visited_type) override;
		void first_visit(Rule& visited_type) override;
		void first_visit(Node& visited_type) override;
		void first_visit(Type& visited_type) override;
		void visit(Type& type) override;
		void visit(Node& node) override;

		void Print(LanguageDefinition& language_definition) override;
	};
}

#endif //DEAMER_LANGUAGEANALYZER_LANGUAGEPRINTER_NODEPRINTER_H