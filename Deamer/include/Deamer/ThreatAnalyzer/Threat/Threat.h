/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_THREAT_THREAT_H
#define DEAMER_THREATANALYZER_THREAT_THREAT_H

#include "Deamer/ThreatAnalyzer/ThreatData/ThreatData.h"

namespace deamer {
	class LanguageDefinition;
}

namespace deamer { namespace threat {
	
	enum class ThreatType;

	class Threat
	{
	private:
	public:
		ThreatData threatData;
		
		Threat(ThreatType type, unsigned threatId);
		virtual ~Threat() = default;

		virtual std::vector<ThreatData> AnalyseLanguageDefinition(const LanguageDefinition& languageDefinition) = 0;

		void SetThreatDescription(const std::string& description);
	};

}}

#endif //DEAMER_THREATANALYZER_THREAT_THREAT_H