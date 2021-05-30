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

#ifndef DEAMER_LEXER_TYPE_FILE_FLEX_TERMINALACTION_H
#define DEAMER_LEXER_TYPE_FILE_FLEX_TERMINALACTION_H

#include "Deamer/Language/Analyzer/Analyzer.h"
#include "Deamer/Language/Type/Definition/Object/Main/Lexicon/Terminal.h"
#include "Deamer/Lexer/Type/Flex/Data.h"

namespace deamer::lexer::type::flex
{
	class TerminalAction : public flex::Data
	{
	private:
		std::string GetDebug() const;
		std::string GetAction() const;
		std::string OptionalAction() const;

		language::analyzer::Analyzer<language::type::definition::object::main::Terminal>
			terminalAnalyzer;

	public:
		TerminalAction(const language::type::definition::object::main::Terminal& terminal_,
					   const ReferenceType reference_);
		~TerminalAction() override = default;

	public:
		std::string ReturnValue() const;
		std::string OptionalReturn() const;
		std::string HandleColumn() const;
		std::string Generate() const override;
	};
}

#endif // DEAMER_LEXER_TYPE_FILE_FLEX_TERMINALACTION_H
