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

#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Language/Type/Definition/Object/Main/Threat/Threat/Analyzer/Deamer/Lexicon/TerminalIsBaseSetOfLaterTerminal.h"

deamer::language::type::definition::object::main::threat::deamer::lexicon::
	TerminalIsBaseSetOfLaterTerminal::TerminalIsBaseSetOfLaterTerminal(
		main::Terminal* terminalSource_, main::Terminal* terminalTarget_)
	: Warning(analyzerType, id),
	  terminalSource(terminalSource_),
	  terminalTarget(terminalTarget_)
{
	references.Add(terminalSource_);
	references.Add(terminalTarget_);
}

bool deamer::language::type::definition::object::main::threat::deamer::lexicon::
	TerminalIsBaseSetOfLaterTerminal::operator==(const TerminalIsBaseSetOfLaterTerminal& rhs) const
{
	return this == &rhs || (this->terminalSource == rhs.terminalSource &&
							this->terminalTarget == rhs.terminalTarget);
}

std::string deamer::language::type::definition::object::main::threat::deamer::lexicon::
	TerminalIsBaseSetOfLaterTerminal::Print() const
{
	return "Terminal: " + this->terminalSource->Name +
		   " Is a base set for later Terminal: " + this->terminalTarget->Name +
		   " This can cause problems if this was not intended.";
}

deamer::language::type::definition::object::main::threat::deamer::lexicon::
	TerminalIsBaseSetOfLaterTerminal::TerminalIsBaseSetOfLaterTerminal()
	: Warning(analyzerType, id),
	  terminalSource(nullptr),
	  terminalTarget(nullptr)
{
}
