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

#ifndef DEAMER_PARSER_GENERATOR_ANTLR_ANTLR_PARSER_H
#define DEAMER_PARSER_GENERATOR_ANTLR_ANTLR_PARSER_H

#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Language/Type/Definition/Property/Type.h"
#include "Deamer/Parser/Generator/Base.h"

namespace deamer::parser::generator::antlr_parser
{
	class Antlr_Parser : public Base
	{
	public:
		using ReferenceType = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar,
			language::type::definition::property::Type::Associativity,
			language::type::definition::property::Type::Precedence>;

	private:
		const ReferenceType reference;
		const std::string name;
		file::tool::Output output{"Antlr_Parser"};

	public:
		Antlr_Parser(ReferenceType reference_);
		~Antlr_Parser() override = default;

	public:
		deamer::file::tool::Output Generate() override;

	private:
		std::unique_ptr<deamer::file::tool::action::Action>
		externalAction(std::optional<deamer::file::tool::File> lexiconFile = std::nullopt,
					   std::optional<deamer::file::tool::File> grammarFile = std::nullopt,
					   bool imported = true);
		std::string externalCMakeLists();
		file::tool::File ListenerTranslate();
		file::tool::File ImportParserHeader();
		file::tool::File ImportParserSource();
		file::tool::File ListenerTranslateSource();
		file::tool::Directory CmakeDirectory();
	};
}

#endif // DEAMER_PARSER_GENERATOR_ANTLR_ANTLR_PARSER_H
