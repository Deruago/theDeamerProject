/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_THREATDATA_THREATDATA_H
#define DEAMER_THREATANALYZER_THREATDATA_THREATDATA_H

#include "Deamer/ThreatAnalyzer/ThreatData/ThreatCodeDescription.h"
#include <string>

namespace deamer { namespace threat {
	
	enum class ThreatType;
	enum class ThreatAnalyzerGroup;

	class ThreatData
	{
	public:
		ThreatType Type;
		std::string ThreatDescription;
		unsigned ThreatId = 0;
		ThreatCodeDescription CodeDescription;

		ThreatData() = default;
		ThreatData(const ThreatType type, const std::string& threatDescription, const unsigned threatId);

		void SetDescription(const std::string& threatDescription);
		void SetCodeDescription(const ThreatCodeDescription& threatCodeDescription);
	};

}}

#endif //DEAMER_THREATANALYZER_THREATDATA_THREATDATA_H