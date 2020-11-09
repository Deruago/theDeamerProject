/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_CODEDESCRIPTIONTYPE_H
#define DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_CODEDESCRIPTIONTYPE_H

namespace deamer { namespace threat {
	
	enum class CodeDescriptionType
	{
		error,
		warning,
		miscellaneous,
	};

}}

#endif //#ifndef DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_CODEDESCRIPTIONTYPE_H