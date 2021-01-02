/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
 /*
  * Part of the DeamerProject.
  * For more information go to: https://github.com/Deruago/theDeamerProject
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
