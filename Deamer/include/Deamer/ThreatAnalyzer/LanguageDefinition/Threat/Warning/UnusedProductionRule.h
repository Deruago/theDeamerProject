/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_WARNING_UNUSEDPRODUCTIONRULE_H
#define DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_WARNING_UNUSEDPRODUCTIONRULE_H

#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefintionThreat.h"
#include "Deamer/ThreatAnalyzer/Threat/WarningThreat.h"

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition { namespace warning {

	class UnusedProductionRule : public WarningThreat, public LanguageDefinitionVisitor
	{
	public:
		const std::string description = "Unused production rules";
		constexpr static unsigned id = static_cast<unsigned>(LanguageDefinitionThreat::unusedProductionRule);
		UnusedProductionRule(const LanguageDefinition& languageDefinition_);

		std::vector<ThreatData> AnalyseLanguageDefinition() override;


	private:
		ThreatData MakeThreatData(Rule* rule) const;
		ThreatCodeDescription MakeThreatCodeDescription(Rule* rule) const;
		std::string MakeErrorDescription(const Rule& rule) const;
		bool ProductionRuleIsInVisitedRules(Rule* rule) const;
		std::vector<Rule*> UsedRules;

		void first_visit(Type& visited_type) override;
		void first_visit(Rule& visited_type) override;
		void first_visit(Node& visited_type) override;
		void visit(Type& type) override;
		void visit(Node& node) override;
	public:
		~UnusedProductionRule() override = default;
	};

}}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_WARNING_UNUSEDPRODUCTIONRULE_H