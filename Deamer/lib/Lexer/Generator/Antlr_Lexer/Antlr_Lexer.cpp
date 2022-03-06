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

#include "Deamer/Lexer/Generator/Antlr_Lexer/Antlr_Lexer.h"
#include "Deamer/Lexer/Type/Antlr/LexerDefinition.h"
#include <utility>

using namespace deamer::language::type::definition::property;

deamer::lexer::generator::antlr_lexer::Antlr_Lexer::Antlr_Lexer(ReferenceType reference_)
	: Base(tool::type::Tool::Antlr_Lexer),
	  reference(reference_),
	  name(reference.GetDefinition<Type::Identity>().GetName()->value)
{
}

deamer::file::tool::Output deamer::lexer::generator::antlr_lexer::Antlr_Lexer::Generate()
{
	const auto Identity = reference.GetDefinition<Type::Identity>();
	const auto Lexicon = reference.GetDefinition<Type::Lexicon>();
	file::tool::Output output("Antlr_Lexer");

	const auto lexerDefinitionGenerator = ::deamer::lexer::type::antlr::LexerDefinition(reference);
	const auto lexerDefinition = file::tool::File(Identity.GetName()->value + "Lexer", "g4",
												  lexerDefinitionGenerator.Generate(),
												  file::tool::GenerationLevel::Always_regenerate);

	output.AddFileToExternal(lexerDefinition);

	return output;
}

std::unique_ptr<deamer::file::tool::action::Action>
deamer::lexer::generator::antlr_lexer::Antlr_Lexer::externalAction()
{
	return {};
}

std::string deamer::lexer::generator::antlr_lexer::Antlr_Lexer::externalCMakeLists()
{
	return {};
}
