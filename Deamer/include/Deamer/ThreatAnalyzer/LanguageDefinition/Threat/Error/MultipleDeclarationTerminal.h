/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONTERMINAL_H
#define DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONTERMINAL_H

#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefintionThreat.h"
#include "Deamer/ThreatAnalyzer/Threat/ErrorThreat.h"

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition { namespace error {

	class MultipleDeclarationTerminal : public ErrorThreat, public LanguageDefinitionVisitor
	{
	public:
		const std::string description = "Redeclared Terminal";
		constexpr static unsigned id = static_cast<unsigned>(LanguageDefinitionThreat::multipleDeclarationTerminal);
		MultipleDeclarationTerminal();

		std::vector<ThreatData> AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition) override;


	private:
		ThreatData MakeThreatData(Node* node) const;
		ThreatCodeDescription MakeThreatCodeDescription(Node* node) const;
		std::string MakeErrorDescription(const Node& node) const;
		bool NonTerminalHasSameNameAsOtherNonTerminal(const Node* a, const Node* b) const;
		bool NonTerminalHasSameNameAsAnyOfAlreadyVisitedTypes(const Node* node) const;
		bool NonTerminalIsInVisitedTypes(Node* node) const;
		bool NonTerminalIsInDuplicatedTypes(const Node* node) const;
		std::vector<Node*> UsedNodes;
		std::vector<Node*> DuplicateNodes;

		void first_visit(Type& visited_type) override;
		void first_visit(Rule& visited_type) override;
		void first_visit(Node& visited_type) override;
		void visit(Type& type) override;
		void visit(Node& node) override;
	public:
		~MultipleDeclarationTerminal() override = default;
	};

}}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONTERMINAL_H