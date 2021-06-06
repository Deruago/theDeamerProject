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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_LEXICON_CRASHTERMINALREFERENCEDINGRAMMAR_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_LEXICON_CRASHTERMINALREFERENCEDINGRAMMAR_H

#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/CheckOutput.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Multi/Multi.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Analyzer/Deamer/Lexicon/CrashTerminalReferencedInGrammar.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Analyzer/Deamer/Lexicon/UnusedTerminal.h"

namespace deamer::language::type::definition::property
{
	class Definition;
}

namespace deamer::language::type::definition::object::main::threat::check::deamer::lexicon
{
	/*! \class CrashTerminalReferencedInGrammar
	 *
	 *  \brief Checks if a Crash terminal was referenced in the grammar LPD.
	 *
	 *  \details Crash terminals never reach the grammar, it is thus useless to reference them.
	 */
	class CrashTerminalReferencedInGrammar
		: public Multi<property::Type::Lexicon, property::Type::Grammar>,
		  public CheckOutput<threat::deamer::lexicon::CrashTerminalReferencedInGrammar>
	{
	protected:
		/*!	\fn AnalyzeDefinition
		 *
		 *	\brief Check for each Crash terminal if it is referenced in the grammar.
		 */
		std::vector<Threat*> AnalyzeDefinition(PropertyReference reference) override
		{
			std::vector<Threat*> threats;

			const auto& lexicon = reference.GetDefinition<property::Type::Lexicon>();

			for (auto* const terminal : lexicon.Terminals)
			{
				if (terminal->Special != SpecialType::Crash)
				{
					continue;
				}

				auto reverseLookup = reference::ReverseLookup<ProductionRule>(&reference);
				const auto& result = reverseLookup.Get(terminal);

				if (!result.IsEmpty())
				{
					threats.push_back(
						new threat::deamer::lexicon::CrashTerminalReferencedInGrammar(terminal));
				}
			}

			return threats;
		}
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_CHECK_MULTI_DEAMER_LEXICON_CRASHTERMINALREFERENCEDINGRAMMAR_H
