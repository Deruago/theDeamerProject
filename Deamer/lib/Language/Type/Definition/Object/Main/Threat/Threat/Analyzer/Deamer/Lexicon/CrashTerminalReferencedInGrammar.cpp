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

#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Analyzer/Deamer/Lexicon/CrashTerminalReferencedInGrammar.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"

deamer::language::type::definition::object::main::threat::deamer::lexicon::
	CrashTerminalReferencedInGrammar::CrashTerminalReferencedInGrammar(main::Terminal* terminal_)
	: Warning(analyzerType, id),
	  terminal(terminal_)
{
	references.Add(terminal);
}

std::string deamer::language::type::definition::object::main::threat::deamer::lexicon::
	CrashTerminalReferencedInGrammar ::Print() const
{
	return "Crash Terminal: " + this->terminal->Name + " is referenced in the Grammar.";
}

deamer::language::type::definition::object::main::threat::deamer::lexicon::
	CrashTerminalReferencedInGrammar::CrashTerminalReferencedInGrammar()
	: Warning(analyzerType, id),
	  terminal(nullptr)
{
}
