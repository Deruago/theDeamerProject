/*
 * Part of the Deamer Project, under the GPLV3 license.
 * Copyright Thimo Bohmer 2020
 *
 * Modified:
 * -November 2020 Thimo Bohmer
 */

#ifndef DEAMER_THREATANALYZER_PRINTER_THREATPRINTER_H
#define DEAMER_THREATANALYZER_PRINTER_THREATPRINTER_H
#include <vector>

#include "Deamer/ThreatAnalyzer/ThreatData/ThreatData.h"
#include "Deamer/Types/Printer/Printer.h"

namespace deamer { namespace threat {
	
	class ThreatPrinter : public types::Printer
	{
	private:
		std::vector<ThreatData> data;
		
		std::string MakeThreatDataHeader(const ThreatData& threatData) const;
		std::string MakeThreatTypePrefix(const ThreatType& type) const;
		std::string MakeThreatTypePrefixMessage(const deamer::threat::ThreatData& threatData) const;
		types::ColorType GetColorBasedOnThreatType(const ThreatType& type) const;

		void PrintThreatDataCodeDescription(const ThreatData& threatData) const;
	public:
		ThreatPrinter(std::vector<ThreatData>& threatData);

		void Print() const;
		void PrintThreatData(const ThreatData& threatData) const;
	};

}}

#endif //DEAMER_THREATANALYZER_PRINTER_THREATPRINTER_H