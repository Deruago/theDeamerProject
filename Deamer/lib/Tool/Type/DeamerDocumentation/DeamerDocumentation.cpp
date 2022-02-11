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

#include "Deamer/Tool/Type/DeamerDocumentation/DeamerDocumentation.h"
#include "Deamer/Language/Reference/ReverseLookup.h"
#include "Deamer/Tool/Type/DeamerDocumentation/Grammar/Grammar.h"
#include "Deamer/Tool/Type/DeamerDocumentation/Lexicon/Lexicon.h"

deamer::tool::type::deamerdocumentation::DeamerDocumentation::DeamerDocumentation(
	reference reference_)
	: Base(::deamer::tool::type::Tool::DeamerDocumentation),
	  Reference(reference_)
{
}

deamer::file::tool::Output deamer::tool::type::deamerdocumentation::DeamerDocumentation::Generate()
{
	const auto language_name =
		Reference.GetDefinition<language::type::definition::property::Type::Identity>()
			.GetName()
			->value;

	file::tool::Output output("DeamerDocumentation");

	lexicon::Lexicon(Reference).Generate(output);
	grammar::Grammar(Reference).Generate(output);

	return output;
}
