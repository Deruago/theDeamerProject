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

#include "Deamer/Language/Type/Definition/Property/Main/Threat.h"
#include <iostream>
#include <utility>

deamer::language::type::definition::property::main::Threat::Threat(
	std::vector<object::main::threat::Threat*> threats_,
	std::vector<object::main::threat::check::CheckInformation> ranChecks)
	: Definition(Type::Threat),
	  RanChecks(std::move(ranChecks))
{
	for (auto* const threat : threats_)
	{
		Threats.push_back(threat);

		Analyzers.insert(threat->GetTypeInformation().analyzerType);
	}
}

deamer::language::type::definition::property::main::Threat::Threat(
	std::vector<const object::main::threat::Threat*> threats_,
	std::vector<object::main::threat::check::CheckInformation> ranChecks)
	: Definition(Type::Threat),
	  RanChecks(std::move(ranChecks)),
	  Threats(std::move(threats_))
{
	references.Add(Threats);
}

std::vector<const deamer::language::type::definition::object::main::threat::Threat*>
deamer::language::type::definition ::property::main::Threat::GetAllThreats() const
{
	return Threats;
}

std::vector<const deamer::language::type::definition::object::main::threat::Threat*>
deamer::language::type::definition ::property::main::Threat::GetAllThreats(
	object::main::threat::analyzer::Type analyzerType) const
{
	std::vector<const object::main::threat::Threat*> threats;
	for (const auto* const threat : Threats)
	{
		if (threat->GetTypeInformation().analyzerType == analyzerType)
		{
			threats.push_back(threat);
		}
	}

	return threats;
}

std::vector<const deamer::language::type::definition::object::main::threat::Threat*>
deamer::language::type::definition ::property::main::Threat::GetAllThreats(
	object::main::threat::Severity severity,
	object::main::threat::analyzer::Type analyzerType) const
{
	std::vector<const object::main::threat::Threat*> threats;
	for (const auto* const threat : Threats)
	{
		if (threat->GetTypeInformation().severity == severity &&
			threat->GetTypeInformation().analyzerType == analyzerType)
		{
			threats.push_back(threat);
		}
	}

	return threats;
}

std::vector<const deamer::language::type::definition::object::main::threat::Threat*>
deamer::language::type::definition::property::main::Threat::GetAllThreats(
	object::main::threat::Severity severity) const
{
	std::vector<const object::main::threat::Threat*> threats;
	for (const auto* const threat : Threats)
	{
		if (threat->GetTypeInformation().severity == severity)
		{
			threats.push_back(threat);
		}
	}

	return threats;
}

std::vector<const deamer::language::type::definition::object::main::threat::Threat*>
deamer::language::type::definition::property::main::Threat::GetAllErrors() const
{
	return GetAllThreats(object::main::threat::Severity::Error);
}

std::vector<const deamer::language::type::definition::object::main::threat::Threat*>
deamer::language::type::definition ::property::main::Threat::GetAllErrors(
	object::main::threat::analyzer::Type analyzerType) const
{
	return GetAllThreats(object::main::threat::Severity::Error, analyzerType);
}

std::vector<const deamer::language::type::definition::object::main::threat::Threat*>
deamer::language::type::definition ::property::main::Threat::GetAllWarnings(
	object::main::threat::analyzer::Type analyzerType) const
{
	return GetAllThreats(object::main::threat::Severity::Warning, analyzerType);
}

std::vector<const deamer::language::type::definition::object::main::threat::Threat*>
deamer::language::type::definition::property::main::Threat::GetAllWarnings() const
{
	return GetAllThreats(object::main::threat::Severity::Warning);
}

void deamer::language::type::definition::property::main::Threat::PrintThreats() const
{
	for (auto analyzer : Analyzers)
	{
		const auto& threatsFromAnalyzer = GetAllThreats(analyzer);
		std::cout << PrintAnalyzerHeader(analyzer) << "\n";
		for (const auto* threats : threatsFromAnalyzer)
		{
			std::cout << threats->GetTypeInformation().Header() + " " + threats->Print() << "\n";
		}
	}
}

std::string deamer::language::type::definition::property::main::Threat::PrintAnalyzerHeader(
	object::main::threat::analyzer::Type value) const
{
	switch (value)
	{
	case object::main::threat::analyzer::Type::Deamer_Lexicon:
		return "Threats found by Deamer Core Lexicon analyzer:";
	case object::main::threat::analyzer::Type::Deamer_Grammar:
		return "Threats found by Deamer Core Grammar analyzer:";
	case object::main::threat::analyzer::Type::Deamer_SymbolTable:
		return "Threats found by Deamer Core SymbolTable analyzer:";
	case object::main::threat::analyzer::Type::Deamer_Precedence:
		return "Threats found by Deamer Core Precedence analyzer:";
	case object::main::threat::analyzer::Type::Deamer_Associativity:
		return "Threats found by Deamer Core Associativity analyzer:";
	case object::main::threat::analyzer::Type::Separator:
		return "Some analyzer choose an invalid id: " +
			   std::to_string(
				   static_cast<std::size_t>(object::main::threat::analyzer::Type::Separator)) +
			   " please report this!";
	default:
	case object::main::threat::analyzer::Type::Unknown:
		return "Threats found by some Analyzer, (not integrated):";
	}
}
