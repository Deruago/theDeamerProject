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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_ANALYZER_ANALYZER_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_ANALYZER_ANALYZER_H

#include "Deamer/Language/Type/Definition/Object/Main/Threat/Analyzer/Base.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/CheckOutput.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Threat.h"
#include <type_traits>
#include <vector>

namespace deamer::language::type::definition::object::main::threat::analyzer
{
	/*! \class Analyzer
	 *
	 *	\tparam ThreatChecks All the checks included in this analyzer
	 */
	template<typename... ThreatChecks>
	class Analyzer
		: public ::deamer::language::type::definition::object::main::threat::analyzer::Base
	{
	public:
		Analyzer() = default;
		virtual ~Analyzer() override = default;

	public:
		template<typename T>
		std::tuple<std::vector<Threat*>, std::vector<check::CheckInformation>>
		Analyze(T languageInformation)
		{
			if constexpr (sizeof...(ThreatChecks) == 0)
			{
				return {};
			}

			std::vector<std::vector<Threat*>> threats;
			std::vector<check::CheckInformation> ranChecks;

			Check<T, ThreatChecks...>(threats, ranChecks, languageInformation);

			std::vector<Threat*> mergeThreats;
			for (auto& threatVector : threats)
			{
				for (auto* const threat : threatVector)
				{
					mergeThreats.push_back(threat);
				}
			}

			return {mergeThreats, ranChecks};
		}

	private:
		template<typename T, typename Check_, typename... Checks_>
		void Check(std::vector<std::vector<Threat*>>& threats,
				   std::vector<check::CheckInformation>& ranChecks, T languageInformation)
		{
			try
			{
				auto check = Check_();
				const std::vector<Threat*> checkFoundThreats = check.Analyze(languageInformation);
				threats.push_back(checkFoundThreats);
				ranChecks.push_back(check.information);

			} catch (exception::RequestedPropertyDefinitionNotFound&)
			{
				/* If we don't have all dependencies for the check to run, ignore the check. */
			}

			if constexpr (sizeof...(Checks_) > 0)
			{
				Check<T, Checks_...>(threats, ranChecks, languageInformation);
			}
		}
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_ANALYZER_ANALYZER_H
