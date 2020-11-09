/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_THREAT_WARNINGTHREAT_H
#define DEAMER_THREATANALYZER_THREAT_WARNINGTHREAT_H
#include "Deamer/ThreatAnalyzer/Threat/Threat.h"

namespace deamer { namespace threat {

	class WarningThreat : public Threat
	{
	private:
	public:
		WarningThreat(const unsigned id);
	};

}}

#endif //DEAMER_THREATANALYZER_THREAT_WARNINGTHREAT_H