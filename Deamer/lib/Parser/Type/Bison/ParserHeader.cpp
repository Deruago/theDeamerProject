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

#include "Deamer/Parser/Type/Bison/ParserHeader.h"
#include "Deamer/Template/Parser/Bison/ParserHeader/ParserHeaderTemplate.h"
#include <memory>

deamer::parser::type::bison::ParserHeader::ParserHeader(
	const generator::bison::Bison::ReferenceType reference_)
	: reference(reference_),
	  name(reference.GetDefinition<language::type::definition::property::Type::Identity>()
			   .GetName()
			   ->value)
{
}

std::string deamer::parser::type::bison::ParserHeader::Generate() const
{
	auto parserHeaderTemplate = std::make_unique<templates::bison::parser::ParserHeaderTemplate>();
	parserHeaderTemplate->language_name_->Set(name);

	return parserHeaderTemplate->GetOutput();
}
