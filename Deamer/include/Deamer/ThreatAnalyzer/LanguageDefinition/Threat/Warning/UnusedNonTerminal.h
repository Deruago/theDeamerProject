/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_WARNING_UNUSEDNONTEMINAL_H
#define DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_WARNING_UNUSEDNONTEMINAL_H

#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefintionThreat.h"
#include "Deamer/ThreatAnalyzer/Threat/WarningThreat.h"

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition { namespace warning {

	class UnusedNonTerminal final : public WarningThreat, public LanguageDefinitionVisitor
	{
	public:
		const std::string description = "Unused Nonterminal";
		constexpr static unsigned id = static_cast<unsigned>(LanguageDefinitionThreat::unusedNonTerminal);
		UnusedNonTerminal();

		std::vector<ThreatData> AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition) override;


	private:
		ThreatData MakeThreatData(Type* type) const;
		ThreatCodeDescription MakeThreatCodeDescription(Type* type) const;
		std::string MakeErrorDescription(const Type& type) const;
		bool NonTerminalIsInVisitedTypes(Type* type) const;
		std::vector<Type*> UsedTypes;
		
		void first_visit(Type& visited_type) override;
		void first_visit(Rule& visited_type) override;
		void first_visit(Node& visited_type) override;
		void visit(Type& type) override;
		void visit(Node& node) override;
	public:
		~UnusedNonTerminal() override = default;
	};

}}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_WARNING_UNUSEDNONTEMINAL_H