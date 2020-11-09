/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/ThreatData/CodeDescription/TokenCodeDescription.h"

deamer::threat::TokenCodeDescription::TokenCodeDescription(Token* token, const std::string& description,
	const CodeDescriptionType type)
{
	Token_ = token;
	Description = description;
	Type = type;
}
