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

#ifndef DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONPRODUCTIONRULE_H
#define DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONPRODUCTIONRULE_H

#include "Deamer/ThreatAnalyzer/LanguageDefinition/LanguageDefintionThreat.h"
#include "Deamer/ThreatAnalyzer/Threat/ErrorThreat.h"

namespace deamer { namespace threat { namespace analyzer { namespace languagedefinition { namespace error {

	class MultipleDeclarationProductionRule : public ErrorThreat
	{
	public:
		const std::string description = "No starting symbol specified";
		constexpr static unsigned id = static_cast<unsigned>(LanguageDefinitionThreat::multipleDeclarationProductionRule);
		MultipleDeclarationProductionRule(const LanguageDefinition& languageDefinition_);

		std::vector<ThreatData> AnalyseLanguageDefinition() override;
	};

}}}}}

#endif //DEAMER_THREATANALYZER_LANGUAGEDEFINITION_THREAT_ERROR_MULTIPLEDECLARATIONPRODUCTIONRULE_H