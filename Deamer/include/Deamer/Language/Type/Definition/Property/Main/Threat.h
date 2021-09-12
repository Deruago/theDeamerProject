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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_THREAT_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_THREAT_H

#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/CheckOutput.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Threat.h"
#include "Deamer/Language/Type/Definition/Property/Main/Definition.h"
#include <vector>

namespace deamer::language::type::definition::property::main
{
	/*! \class Threat
	 *
	 *  \brief Language Property Definition of the various threats in the LD.
	 *  Used to specify all the found threats in language X.
	 *
	 *  \note This is part of the special LPD's, and thus always included in references.
	 */
	class Threat final : public Definition
	{
	public:
		std::set<object::main::threat::analyzer::Type> Analyzers;
		std::vector<object::main::threat::check::CheckInformation> RanChecks;

		std::vector<const object::main::threat::Threat*> Threats;

	public:
		Threat(std::vector<object::main::threat::Threat*> threats_,
			   std::vector<object::main::threat::check::CheckInformation> ranChecks);
		Threat(std::vector<const object::main::threat::Threat*> threats_,
			   std::vector<object::main::threat::check::CheckInformation> ranChecks);

		virtual ~Threat() = default;

	public:
		std::vector<const object::main::threat::Threat*> GetAllThreats() const;

		std::vector<const object::main::threat::Threat*>
		GetAllThreats(object::main::threat::analyzer::Type analyzerType) const;

		std::vector<const object::main::threat::Threat*>
		GetAllThreats(object::main::threat::Severity severity) const;

		std::vector<const object::main::threat::Threat*>
		GetAllThreats(object::main::threat::Severity severity,
					  object::main::threat::analyzer::Type analyzerType) const;

		std::vector<const object::main::threat::Threat*> GetAllErrors() const;
		std::vector<const object::main::threat::Threat*>
		GetAllErrors(object::main::threat::analyzer::Type analyzerType) const;

		std::vector<const object::main::threat::Threat*> GetAllWarnings() const;
		std::vector<const object::main::threat::Threat*>
		GetAllWarnings(object::main::threat::analyzer::Type analyzerType) const;

		template<typename T, std::enable_if_t<std::is_enum_v<T>, bool> = true>
		std::vector<const object::main::threat::Threat*>
		GetAllThreatsOfTypeAndAnalyzer(object::main::threat::analyzer::Type analyzerType,
									   T id) const;

		template<typename T, std::enable_if_t<std::is_enum_v<T>, bool> = true>
		bool IsThreatRan(object::main::threat::analyzer::Type analyzerType, T id) const;

		void PrintThreats() const;

	private:
		std::string PrintAnalyzerHeader(object::main::threat::analyzer::Type value) const;
	};

	template<typename T, std::enable_if_t<std::is_enum_v<T>, bool>>
	std::vector<const object::main::threat::Threat*>
	Threat::GetAllThreatsOfTypeAndAnalyzer(object::main::threat::analyzer::Type analyzerType,
										   T id) const
	{
		std::vector<const object::main::threat::Threat*> output;

		for (auto* const threat : Threats)
		{
			if (threat->GetTypeInformation().analyzerType == analyzerType &&
				threat->GetTypeInformation().id == static_cast<std::size_t>(id))
			{
				output.push_back(threat);
			}
		}

		return output;
	}

	template<typename T, std::enable_if_t<std::is_enum_v<T>, bool>>
	bool Threat::IsThreatRan(object::main::threat::analyzer::Type analyzerType, T id) const
	{
		for (auto& ranCheck : RanChecks)
		{
			if (ranCheck.id == static_cast<std::size_t>(id) && ranCheck.analyzer == analyzerType)
			{
				return true;
			}
		}

		return false;
	}
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_PROPERTY_MAIN_THREAT_H
