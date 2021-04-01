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

#include "Deamer/Parser/Generator/Bison/Bison.h"
#include "Deamer/Parser/Type/Bison/Output.h"

deamer::parser::generator::bison::Bison::Bison(const ReferenceType reference_)
	: Base(tool::type::Tool::Bison),
	  reference(reference_)
{
}

deamer::file::tool::Output deamer::parser::generator::bison::Bison::Generate()
{
	file::tool::Output output("Bison");
	type::bison::Output bisonFileData(reference);

	const auto& lexicon =
		reference.GetDefinition<language::type::definition::property::Type::Lexicon>();
	const auto& grammar =
		reference.GetDefinition<language::type::definition::property::Type::Grammar>();

	for (const auto* const terminal : lexicon.Terminals)
	{
		bisonFileData.AddTerminal(terminal);
	}

	for (const auto* const nonTerminal : grammar.NonTerminals)
	{
		bisonFileData.AddNonTerminal(nonTerminal);
	}

	std::cout << bisonFileData.Generate() << std::endl;

	return output;
}
