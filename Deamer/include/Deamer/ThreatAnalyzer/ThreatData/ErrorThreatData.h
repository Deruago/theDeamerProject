/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_THREATDATA_ERRORTHREATDATA_H
#define DEAMER_THREATANALYZER_THREATDATA_ERRORTHREATDATA_H
#include "Deamer/ThreatAnalyzer/ThreatData/ThreatData.h"

namespace deamer { namespace threat {

	class ErrorThreatData : public ThreatData
	{
	private:
	public:
		ErrorThreatData(const std::string& description, unsigned id);
	};

}}

#endif //DEAMER_THREATANALYZER_THREATDATA_ERRORTHREATDATA_H