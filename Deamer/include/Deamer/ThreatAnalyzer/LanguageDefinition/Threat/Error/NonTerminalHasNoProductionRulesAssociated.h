/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_NONTERMINALHASNOPRODUCTIONRULESASSOCIATED_H
#define DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_NONTERMINALHASNOPRODUCTIONRULESASSOCIATED_H

#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefintionThreat.h"
#include "Deamer/ThreatAnalyzer/Threat/ErrorThreat.h"

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition { namespace error {

	class NonTerminalHasNoProductionRulesAssociated : public ErrorThreat, public LanguageDefinitionVisitor
	{
	public:
		const std::string description = "NonTerminal doesn't have any production-rules";
		constexpr static unsigned id = static_cast<unsigned>(LanguageDefinitionThreat::nonTerminalHasNoProductionRulesAssociated);
		NonTerminalHasNoProductionRulesAssociated();

		std::vector<ThreatData> AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition) override;


	private:
		ThreatData MakeThreatData(Type* type) const;
		ThreatCodeDescription MakeThreatCodeDescription(Type* type) const;
		std::string MakeErrorDescription(const Type& type) const;
		bool NonTerminalHasProductionRules(const Type* type) const;
		bool NonTerminalIsInVisitedTypes(const Type* type) const;
		std::vector<Type*> UsedTypes;

		void first_visit(Type& visited_type) override;
		void first_visit(Rule& visited_type) override;
		void first_visit(Node& visited_type) override;
		void visit(Type& type) override;
		void visit(Node& node) override;
	public:
		~NonTerminalHasNoProductionRulesAssociated() override = default;
	};

}}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_NONTERMINALHASNOPRODUCTIONRULESASSOCIATED_H