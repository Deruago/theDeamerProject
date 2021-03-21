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

#ifndef DEAMER_LEXER_TYPE_FILE_FLEX_OUTPUT_H
#define DEAMER_LEXER_TYPE_FILE_FLEX_OUTPUT_H

#include "Deamer/Lexer/Type/Flex/IncludeSection.h"
#include "Deamer/Lexer/Type/Flex/MainSection.h"
#include "Deamer/Lexer/Type/Flex/TerminalActionSection.h"
#include "Deamer/Lexer/Type/Flex/TerminalDeclarationSection.h"

namespace deamer::lexer::type::flex
{
	class Output : public TerminalDeclarationSection, public TerminalActionSection
	{
	private:
		const generator::flex::Flex::ReferenceType reference;

		TerminalDeclarationSection declarationSection;
		TerminalActionSection actionSection;
		IncludeSection includeSection;
		MainSection mainSection;

	public:
		Output(const generator::flex::Flex::ReferenceType reference_);
		~Output() override = default;

	public:
		void AddTerminal(const language::type::definition::object::main::Terminal& terminal);

		std::string Generate() const override;
	};
}

#endif // DEAMER_LEXER_TYPE_FILE_FLEX_OUTPUT_H
