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

#ifndef DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_ANALYZER_COMBINED_DEAMER_DEAMERCORE_H
#define DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_ANALYZER_COMBINED_DEAMER_DEAMERCORE_H

#include "Deamer/Language/Type/Definition/Object/Main/Threat/Analyzer/Analyzer.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Multi/Deamer/Lexicon/CrashTerminalReferencedInGrammar.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Multi/Deamer/Lexicon/DeletedTerminalReferencedInGrammar.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Multi/Deamer/Lexicon/UnusedTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Single/Deamer/Grammar/UnusedNonTerminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Check/Single/Deamer/Grammar/UnusedProductionRule.h"

namespace deamer::language::type::definition::object::main::threat::analyzer::deamer
{
	/*! \class DeamerCore
	 *
	 */
	class DeamerCore final
		: public Analyzer<check::deamer::lexicon::UnusedTerminal,
						  check::deamer::lexicon::CrashTerminalReferencedInGrammar,
						  check::deamer::lexicon::DeletedTerminalReferencedInGrammar,
						  check::deamer::grammar::UnusedNonTerminal,
						  check::deamer::grammar::UnusedProductionRule>
	{
	};
}

#endif // DEAMER_LANGUAGE_DATASTRUCTURE_DEFINITION_OBJECT_MAIN_THREAT_ANALYZER_COMBINED_DEAMER_DEAMERCORE_H
