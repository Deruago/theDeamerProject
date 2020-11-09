/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_THREAT_ERRORTHREAT_H
#define DEAMER_THREATANALYZER_THREAT_ERRORTHREAT_H
#include "Deamer/ThreatAnalyzer/Threat/Threat.h"

namespace deamer { namespace threat {

	class ErrorThreat : public Threat
	{
	private:
	public:
		ErrorThreat(const unsigned id);
	};

}}

#endif //DEAMER_THREATANALYZER_THREAT_ERRORTHREAT_H