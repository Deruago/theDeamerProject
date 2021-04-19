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

#ifndef DEAMER_LEXER_TYPE_FILE_FLEX_INCLUDESECTION_H
#define DEAMER_LEXER_TYPE_FILE_FLEX_INCLUDESECTION_H

#include "Deamer/File/Tool/Data.h"
#include "Deamer/Lexer/Generator/Flex/Flex.h"

namespace deamer::lexer::type::flex
{
	class IncludeSection : public file::tool::Data
	{
	private:
		using ReferenceType = deamer::lexer::generator::flex::Flex::ReferenceType;
		ReferenceType reference;
		const std::string name;

	public:
		IncludeSection(ReferenceType reference_);
		~IncludeSection() override = default;

	public:
		std::string Generate() const override;

	private:
		std::string ParserInclude() const;
		std::string ParserMacroRedefine() const;
		std::string RedefineMacros() const;
		std::string LexerIncludeLocation() const;
		std::string InteractiveOption() const;
		std::string UnistdOption() const;
		std::string LanguageInclude() const;
	};
}

#endif // DEAMER_LEXER_TYPE_FILE_FLEX_INCLUDESECTION_H
