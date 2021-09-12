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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_THREAT_ANALYZER_DEAMER_GRAMMAR_UNUSEDPRODUCTIONRULE_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_THREAT_ANALYZER_DEAMER_GRAMMAR_UNUSEDPRODUCTIONRULE_H

#include "Deamer/Language/Analyzer/Main/Grammar/ProductionRule.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Analyzer/Deamer/Grammar/Type.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Warning.h"
#include "Deamer/Type/Memory/SafeReserve.h"

namespace deamer::language::type::definition::object::main::threat::deamer::grammar
{
	/*! \class UnusedProductionRule
	 *
	 */
	class UnusedProductionRule : public Warning
	{
		friend ::deamer::type::SafeReserve<UnusedProductionRule>;

	public:
		static constexpr ::deamer::language::type::definition::object::main::threat::deamer::
			grammar::Type id = Type::UnusedProductionRule;
		static constexpr auto analyzerType = analyzer::Type::Deamer_Grammar;

		::deamer::language::type::definition::object::main::ProductionRule* ProductionRule;

	public:
		UnusedProductionRule(
			::deamer::language::type::definition::object::main::ProductionRule* productionRule_);

		~UnusedProductionRule() = default;

		std::string Print() const override;

	protected:
		UnusedProductionRule();
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_THREAT_ANALYZER_DEAMER_GRAMMAR_UNUSEDPRODUCTIONRULE_H
