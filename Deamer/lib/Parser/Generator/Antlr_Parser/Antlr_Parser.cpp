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

#include "Deamer/Parser/Generator/Antlr_Parser/Antlr_Parser.h"
#include "Deamer/Parser/Type/Antlr/ParserDefinition.h"

deamer::parser::generator::antlr_parser::Antlr_Parser::Antlr_Parser(const ReferenceType reference_)
	: Base(tool::type::Tool::Antlr_Parser),
	  reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .GetName()
			   ->value)
{
}

deamer::file::tool::Output deamer::parser::generator::antlr_parser::Antlr_Parser::Generate()
{
	file::tool::Output output("Antlr_Parser");

	const auto parserDefinitionGenerator =
		::deamer::parser::type::antlr::ParserDefinition(reference);
	const auto parserDefinition =
		file::tool::File(name + "Parser", "g4", parserDefinitionGenerator.Generate(),
						 file::tool::GenerationLevel::Always_regenerate);

	output.AddFileToExternal(parserDefinition);

	return output;
}

deamer::file::tool::Action deamer::parser::generator::antlr_parser::Antlr_Parser::externalAction()
{
	return {};
}

std::string deamer::parser::generator::antlr_parser::Antlr_Parser::externalCMakeLists()
{
	return {};
}
