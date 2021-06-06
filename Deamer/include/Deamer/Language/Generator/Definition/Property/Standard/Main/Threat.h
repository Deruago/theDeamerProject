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

#ifndef DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_MAIN_THREAT_H
#define DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_MAIN_THREAT_H

#include "Deamer/Language/Generator/Definition/Property/Standard/Base.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Analyzer/Analyzer.h"
#include "Deamer/Language/Type/Definition/Property/Main/Threat.h"

namespace deamer::language::generator::definition::property::standard
{
	template<typename LanguageDefinitionType, typename... ThreatAnalyzers>
	class Threat : public Base<LanguageDefinitionType, type::definition::property::main::Threat>
	{
	public:
		Threat(LanguageDefinitionType* language_)
			: standard::Base<LanguageDefinitionType, type::definition::property::main::Threat>(
				  language_)
		{
		}
		~Threat() override = default;

		void GenerateObjects() override
		{
			this->template AnalyzeThreats<ThreatAnalyzers...>();
		}

		/*!	\fn Generate
		 *
		 *	\brief Generates a default precedence property definition.
		 *
		 *	\details The default precedence definition exists of a set of precedences which are all
		 *the same (0).
		 */
		void GenerateDefinition() override
		{
			auto Threats = Base<LanguageDefinitionType, type::definition::property::main::Threat>::
				template GetObjects<type::definition::object::Type::Threat>();
			this->generatedDefinition =
				new type::definition::property::main::Threat(Threats, ranChecks);
		}

	private:
		std::vector<
			::deamer::language::type::definition::object::main::threat::check::CheckInformation>
			ranChecks;

		template<typename ThreatAnalyzer_,
				 std::enable_if_t<
					 std::is_base_of_v<type::definition::object::main::threat::analyzer::Base,
									   ThreatAnalyzer_>,
					 bool> = true,
				 typename... ThreatAnalyzers_>
		void AnalyzeThreats()
		{
			auto threats_and_ranchecks = ThreatAnalyzer_().Analyze(this->GetLanguageReference());

			for (auto* const threat : std::get<0>(threats_and_ranchecks))
			{
				this->AddObject(threat);
			}

			for (auto& rancheck : std::get<1>(threats_and_ranchecks))
			{
				this->ranChecks.push_back(rancheck);
			}

			if constexpr (sizeof...(ThreatAnalyzers_) > 0)
			{
				AnalyzeThreats<ThreatAnalyzers_...>();
			}
		}
	};
}

#endif // DEAMER_LANGUAGE_GENERATOR_DEFINITION_PROPERTY_STANDARD_MAIN_THREAT_H
