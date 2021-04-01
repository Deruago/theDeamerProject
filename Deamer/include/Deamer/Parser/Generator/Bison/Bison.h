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
#ifndef DEAMER_PARSER_GENERATOR_BISON_BISON_H
#define DEAMER_PARSER_GENERATOR_BISON_BISON_H

#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Language/Type/Definition/Property/Type.h"
#include "Deamer/Parser/Generator/Base.h"

namespace deamer::parser::generator::bison
{
	class Bison : public Base
	{
	public:
		using ReferenceType = language::reference::PropertyDefinition<
			language::type::definition::property::Type::Lexicon,
			language::type::definition::property::Type::Grammar,
			language::type::definition::property::Type::Associativity,
			language::type::definition::property::Type::Precedence>;

	private:
		const ReferenceType reference;

	public:
		Bison(ReferenceType reference_);
		~Bison() override = default;

	public:
		deamer::file::tool::Output Generate() override;
	};
}

#endif // DEAMER_PARSER_GENERATOR_BISON_BISON_H
