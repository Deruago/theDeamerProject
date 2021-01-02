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