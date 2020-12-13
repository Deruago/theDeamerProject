/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_EMPTYRECURSION_H
#define DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_EMPTYRECURSION_H

#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefintionThreat.h"
#include "Deamer/ThreatAnalyzer/Threat/ErrorThreat.h"
#include "Deamer/LanguageGen/LanguageDefinition.h"

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition { namespace error {

	class EmptyRecursion : public ErrorThreat, public LanguageDefinitionVisitor
	{
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
		const std::string description = "Non Terminal Empty recursion";
		constexpr static unsigned id = static_cast<unsigned>(LanguageDefinitionThreat::emptyRecursion);
		EmptyRecursion(const LanguageDefinition& languageDefinition_);

		std::vector<ThreatData> AnalyseLanguageDefinition() override;
	public:
		~EmptyRecursion() override = default;
	};

}}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_EMPTYRECURSION_H