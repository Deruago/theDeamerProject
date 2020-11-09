/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_THREATTYPE_H
#define DEAMER_THREATANALYZER_THREATTYPE_H

namespace deamer { namespace threat {
	
	enum class ThreatType
	{
		warning,
		error,
		miscellaneous,
	};

}}

#endif //DEAMER_THREATANALYZER_THREATTYPE_H