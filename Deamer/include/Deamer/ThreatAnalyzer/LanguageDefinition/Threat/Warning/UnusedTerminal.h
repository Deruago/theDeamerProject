/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_WARNING_UNUSEDTEMINAL_H
#define DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_WARNING_UNUSEDTEMINAL_H

#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefintionThreat.h"
#include "Deamer/ThreatAnalyzer/Threat/WarningThreat.h"

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition { namespace warning {

	class UnusedTerminal : public WarningThreat , public LanguageDefinitionVisitor
	{
	public:
		const std::string description = "Unused Terminal";
		constexpr static unsigned id = static_cast<unsigned>(LanguageDefinitionThreat::unusedTerminal);
		UnusedTerminal();

		std::vector<ThreatData> AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition) override;


	private:
		ThreatData MakeThreatData(Node* node) const;
		ThreatCodeDescription MakeThreatCodeDescription(Node* node) const;
		std::string MakeErrorDescription(const Node& node) const;
		bool TerminalIsInVisitedNodes(Node* node) const;
		std::vector<Node*> UsedNodes;

		void first_visit(Type& visited_type) override;
		void first_visit(Rule& visited_type) override;
		void first_visit(Node& visited_type) override;
		void visit(Type& type) override;
		void visit(Node& node) override;
	public:
		~UnusedTerminal() override = default;
	};
	};

}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_WARNING_UNUSEDTEMINAL_H