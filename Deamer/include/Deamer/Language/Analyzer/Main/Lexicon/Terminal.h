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

#ifndef DEAMER_LANGUAGE_ANALYZER_MAIN_LEXICON_TERMINAL_H
#define DEAMER_LANGUAGE_ANALYZER_MAIN_LEXICON_TERMINAL_H

#include "Deamer/Language/Analyzer/Main/Base.h"

namespace deamer::language::analyzer::main
{
	class Terminal : public Base
	{
	private:
		deamer::language::type::definition::object::main::Terminal* const terminal;

	public:
		Terminal(const reference::PropertyDefinitionBase* reference_,
				 deamer::language::type::definition::object::main::Terminal* terminal_);
		~Terminal() override = default;

	public:
	};
}

#endif // DEAMER_LANGUAGE_ANALYZER_MAIN_LEXICON_TERMINAL_H
