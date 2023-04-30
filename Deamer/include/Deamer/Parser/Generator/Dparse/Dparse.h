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

#ifndef DEAMER_PARSER_GENERATOR_DPARSE_DPARSE_H
#define DEAMER_PARSER_GENERATOR_DPARSE_DPARSE_H

#include "Deamer/Language/Reference/PropertyDefinition.h"
#include "Deamer/Language/Type/Definition/Property/Type.h"
#include "Deamer/Parser/Generator/Base.h"
#include "Deamer/Type/Enum/BitwiseEnum.h"

namespace deamer::parser::generator::dparse
{
	enum class Algorithm
	{
		Uknown = 0,
		LR = 1,
		LALR = 2,
		SLR = 4,
		Adaptive = 8,
		General = 16,
	};

	class Dparse : public Base
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
		::deamer::type::BitwiseEnum<Algorithm> algorithm = Algorithm::LR;

	public:
		Dparse(ReferenceType reference_);
		~Dparse() override = default;

	public:
		deamer::file::tool::Output Generate() override;

	private:
		deamer::file::tool::Output ConstructLR1();
		file::tool::Output ConstructSLR();
		file::tool::Output ConstructLALR();
		file::tool::Output ConstructAdaptiveLALR();
		file::tool::Output ConstructIELR();

		file::tool::Output ConstructGLR();
		file::tool::Output ConstructGSLR();
		file::tool::Output ConstructGLALR();
		file::tool::Output ConstructGAdaptiveLALR();

		file::tool::Output ConstructLRK();
		file::tool::Output ConstructLAKLRM();

		file::tool::Output ConstructLL1();
		file::tool::Output ConstructLLK();
		file::tool::Output ConstructGLL1();
		file::tool::Output ConstructGLLK();
		file::tool::Output ConstructRecursiveDescent();
	};
}

#endif // DEAMER_PARSER_GENERATOR_DPARSE_DPARSE_H
