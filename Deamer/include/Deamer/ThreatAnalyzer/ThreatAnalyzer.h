/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_THREATANALYZER_H
#define DEAMER_THREATANALYZER_THREATANALYZER_H

#include "Deamer/ThreatAnalyzer/ThreatData/ThreatData.h"
#include <vector>

namespace deamer {
	class LanguageDefinition;
}

namespace deamer { namespace threat {

	class ThreatAnalyzer
	{
	private:
	public:
		ThreatAnalyzer() = default;
		virtual ~ThreatAnalyzer() = default;

		virtual std::vector<ThreatData> AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition) const = 0;
		bool DoesThreatDataContainErrors(const std::vector<ThreatData>& threatData) const;
		bool DoesThreatDataContainWarnings(const std::vector<ThreatData>& threatData) const;
	};

}}

#endif //DEAMER_THREATANALYZER_THREATANALYZER_H