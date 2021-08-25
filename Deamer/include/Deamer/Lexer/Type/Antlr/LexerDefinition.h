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

#ifndef DEAMER_LEXER_TYPE_ANTLR_LEXERDEFINITION_H
#define DEAMER_LEXER_TYPE_ANTLR_LEXERDEFINITION_H

#include "Deamer/File/Tool/Data.h"
#include "Deamer/Language/Reference/PropertyDefinition.h"

namespace deamer::lexer::type::antlr
{
	class LexerDefinition : public file::tool::Data
	{
	public:
		using ReferenceType = ::deamer::language::reference::PropertyDefinition<
			::deamer::language::type::definition::property::Type::Lexicon,
			::deamer::language::type::definition::property::Type::Grammar>;

	private:
		const ReferenceType reference;

	public:
		LexerDefinition(ReferenceType reference_);
		~LexerDefinition() = default;

	public:
		std::string Generate() const override;
	};
}

#endif // DEAMER_LEXER_TYPE_ANTLR_LEXERDEFINITION_H
