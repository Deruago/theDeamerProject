/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_TOKENCODEDESCRIPTION_H
#define DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_TOKENCODEDESCRIPTION_H

#include "Deamer/ThreatAnalyzer/ThreatData/CodeDescription/CodeDescriptionType.h"
#include "Deamer/LanguageGen/LanguageDefinitionDataStructures/Token.h"
#include <string>

namespace deamer { namespace threat {

	class TokenCodeDescription
	{
	public:
		Token* Token_;
		std::string Description;
		CodeDescriptionType Type;
		
		TokenCodeDescription(Token* token, const std::string& description, const CodeDescriptionType type);
	};
	
}}

#endif //DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_TOKENCODEDESCRIPTION_H