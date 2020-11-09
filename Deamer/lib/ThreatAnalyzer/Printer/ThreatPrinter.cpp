/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#include "Deamer/ThreatAnalyzer/Printer/ThreatPrinter.h"
#include "Deamer/ThreatAnalyzer/ThreatType.h"
#include <iostream>

deamer::threat::ThreatPrinter::ThreatPrinter(std::vector<ThreatData>& threatData)
{
	data = threatData;
}

void deamer::threat::ThreatPrinter::Print() const
{
	for (const auto& theadData : data)
	{
		PrintThreatData(theadData);
	}
}

void deamer::threat::ThreatPrinter::PrintThreatData(const ThreatData& threatData) const
{
	const auto PrefixMessage = MakeThreatTypePrefixMessage(threatData);
	Output(PrefixMessage, GetColorBasedOnThreatType(threatData.Type));

	const auto HeaderMessage = MakeThreatDataHeader(threatData);
	Output(HeaderMessage);

	PrintThreatDataCodeDescription(threatData);
}

std::string deamer::threat::ThreatPrinter::MakeThreatDataHeader(const ThreatData& threatData) const
{
	return threatData.ThreatDescription + "\n";
}

std::string deamer::threat::ThreatPrinter::MakeThreatTypePrefixMessage(const ThreatData& threatData) const
{
	return MakeThreatTypePrefix(threatData.Type) + "[" + std::to_string(threatData.ThreatId) + "]" + ": ";
}

std::string deamer::threat::ThreatPrinter::MakeThreatTypePrefix(const ThreatType& type) const
{
	switch (type)
	{
	case ThreatType::error:
		return "ERROR";
	case ThreatType::warning:
		return "WARNING";
	case ThreatType::miscellaneous:
		return "OTHER";
	}
	return "";
}

deamer::types::ColorType deamer::threat::ThreatPrinter::GetColorBasedOnThreatType(const ThreatType& type) const
{
	switch (type)
	{
	case ThreatType::error:
		return types::ColorType::Red;
	case ThreatType::warning:
		return types::ColorType::Magenta;
	case ThreatType::miscellaneous:
		return types::ColorType::Blue;
	}
	return types::ColorType::White;
}

void deamer::threat::ThreatPrinter::PrintThreatDataCodeDescription(const ThreatData& threatData) const
{
	
}
