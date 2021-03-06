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

#ifndef DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_PRODUCTIONRULECODEDESCRIPTION_H
#define DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_PRODUCTIONRULECODEDESCRIPTION_H

#include "Deamer/ThreatAnalyzer/ThreatData/CodeDescription/CodeDescriptionType.h"
#include <vector>
#include <string>

namespace deamer { namespace threat {
	class TokenCodeDescription;
	
	class ProductionRuleCodeDescription
	{
	public:
		std::vector<TokenCodeDescription*> TokenDescriptions;
		CodeDescriptionType Type;
		std::string Description;
		bool CompleteProductionRule;
		
		ProductionRuleCodeDescription(std::vector<TokenCodeDescription*> tokenDescriptions, std::string description, bool completeProductionRule, CodeDescriptionType type);
	};

}}

#endif //DEAMER_THREATANALYZER_THREATDATA_CODEDESCRIPTION_PRODUCTIONRULECODEDESCRIPTION_H