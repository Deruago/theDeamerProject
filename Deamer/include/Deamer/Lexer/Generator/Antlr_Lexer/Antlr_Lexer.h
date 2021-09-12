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

#ifndef DEAMER_LEXER_GENERATOR_ANTLR_H
#define DEAMER_LEXER_GENERATOR_ANTLR_H

#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Lexer/Generator/Base.h"

namespace deamer::lexer::generator::antlr_lexer
{
	class Antlr_Lexer : public Base
	{
	public:
		using ReferenceType = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar>;

	private:
		const ReferenceType reference;
		const std::string name;

	public:
		Antlr_Lexer(ReferenceType reference_);
		~Antlr_Lexer() override = default;

	public:
		deamer::file::tool::Output Generate() override;

	private:
		deamer::file::tool::Action externalAction();
		std::string externalCMakeLists();
	};
}

#endif // DEAMER_LEXER_GENERATOR_ANTLR_H